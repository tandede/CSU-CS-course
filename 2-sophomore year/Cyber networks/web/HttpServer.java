import java.net.ServerSocket;
import java.net.Socket;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class HttpServer {
    public static void main(String[] args) {
        ServerSocket serverSocket = null;
        try {
            // 创建服务器套接字
            serverSocket = new ServerSocket(8080);
        } catch (IOException ioe) {
            ioe.printStackTrace();
            System.exit(0);
        }
        Socket socket = null;
        InputStream inputStream = null;
        OutputStream outputStream = null;
        while (true) {
            try {
                // 接受套接字请求并创建相应的服务器套接字来启动监听
                socket = serverSocket.accept();
                // 获取输入流
                inputStream = socket.getInputStream();
                // 获取输出流
                outputStream = socket.getOutputStream();
                // 实例化请求类
                Request request = new Request(inputStream);
                // 实例化应答类
                Response response = new Response(outputStream, request);
                // 解析请求
                request.parse();
                // 根据请求做响应应答
                response.sendStaticSourse();
                // 关闭套接字
                socket.close();
            } catch (IOException ioe) {
                ioe.printStackTrace();
            }
        }
    }
}