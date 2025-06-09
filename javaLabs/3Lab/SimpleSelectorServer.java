import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

public class SimpleSelectorServer {
    private static final int PORT = 9999;
    private static final int BUFFER_SIZE = 1024;
    static HashSet<SocketChannel> connectedClients = new HashSet<SocketChannel>() {
    };

    // Простой сервер!
    public static void main(String[] args) throws IOException {
        // 1. Создали селектор
        Selector selector = Selector.open();

        // 2. Создаём серверный сокет (один на всю программу в нашем случае!)
        ServerSocketChannel serverChannel = ServerSocketChannel.open();
        serverChannel.bind(new InetSocketAddress(PORT));
        serverChannel.configureBlocking(false);
        serverChannel.register(selector, SelectionKey.OP_ACCEPT);

        ByteBuffer buffer = ByteBuffer.allocate(BUFFER_SIZE);

        while (true) {
            // Блокируемся на селекторе, ждём входящих соединений!
            System.out.println("Waiting for clients");
            selector.select();
            System.out.println("Accepted client!");

            // Вывалились из селекта, обрабатываем отстрелившиеся соединения
            Set<SelectionKey> selectedKeys = selector.selectedKeys();
            Iterator<SelectionKey> iter = selectedKeys.iterator();

            // Перебираем соединения, проверяем их статус, обрабатываем
            while (iter.hasNext()) {
                SelectionKey key = iter.next();

                // новое соединение!!!
                if (key.isAcceptable()) {
                    ServerSocketChannel srv = (ServerSocketChannel) key.channel();
                    SocketChannel client = srv.accept();
                    client.configureBlocking(false);

                    // создали новый сокет и добавляем его в селектор для дальнейшего чтения
                    client.register(selector, SelectionKey.OP_READ);
                    System.out.println("Accepted new connection from " + client.getRemoteAddress());
                    // В соединение приехали новые данные, читаем их
                    connectedClients.add(client);
                } else if (key.isReadable()) {
                    SocketChannel client = (SocketChannel) key.channel();
                    buffer.clear();

                    // ЗАПУСТИТЬ ОБРАБОТЧИК СООБЩЕНИЯ!
                    // НА ТРЕДПУЛЕ
                    int read = client.read(buffer);
                    if (read == -1) {
                        client.close();
                        /// ??????? !!!!!!!!!!!
                    } else {
                        // Печатаем входящее сообщение
                        String message = new String(buffer.array(), 0, read).trim();
                        System.out.println("Received: " + message);
                        // пересылаем остальеым клиентам
                        sendMessageToClients(message, client);

                    }
                }
                iter.remove();
            }
        }
    }

    public static void sendMessageToClients(String message, SocketChannel initiator) throws IOException {
        ByteBuffer bufferToSend = ByteBuffer.wrap(message.getBytes());
        // чаннелы работают только с буфферами
        for (SocketChannel client : connectedClients) {
            if (client == initiator) {
                continue;
            }
            if (!client.isConnected()) {
                continue;
            }
            client.write(bufferToSend);
            bufferToSend.rewind();
        }

    }
}
