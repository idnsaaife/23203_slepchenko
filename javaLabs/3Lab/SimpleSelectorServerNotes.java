
while (true) {
    //blokiruemsya
    selector.select();
    System.out.println("Accepted client!");
    Set<SelectionKey> selectedKeys = selector.selectedKeys();

    Iterator<SelectionKey> iter = selectedKeys.iterator();
ByteBuffer buffer = ByteBuffer.allocate(Buffer_SIZE);
    //перебираем соединения смоттрим в каком они статусе
    while (iter.hasNext()){
        //новое соединение
    if (key.isAcceptable()) {
        ServerSocketChannel srv = (ServerSocketChannel) key.channel();
        SocketChannel client = srv.accept();
        client.configureBlocking(false);
        client.register(selector, SelectionKey.OP_READ);
    } else if(key.isReadable()) {
        SocketChannel client = (SocketChannel) key.channel();
        buffer.clear();

        //ЗАПУСТИТЬ ОБРАБОТЧИК СООБЩЕНИЯ на трэдпуле можно взять executor

        int read = client.read(buffer);
        if (read == -1) {
            client.close();
        } else {
            //печатаем входящее сообщение
            
            String message = new String(buffer.array(), 0, read).trim();
        }
    }
    iter.remove();
}
}