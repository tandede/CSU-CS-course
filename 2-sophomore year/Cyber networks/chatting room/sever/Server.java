import java.awt.BorderLayout;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

import javax.swing.JFrame;
import javax.swing.JTextArea;

// 服务器类
public class Server extends JFrame implements Runnable {
    private ServerSocket ss = null;
    private JTextArea jta = new JTextArea();
    // 存储正在运行的用户线程
    private ArrayList<ChatThread> chatThread = new ArrayList<ChatThread>();

    public Server() throws Exception {
        this.setTitle("服务器");
        this.setSize(300, 400);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setVisible(true);
        this.add(jta, BorderLayout.NORTH);
        ss = new ServerSocket(8080);
        new Thread(this).start();
    }

    // 线程运行内容
    public void run() {
        while (true) {
            try {
                Socket socket = this.ss.accept();
                // 解析用户登录信息
                BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                String msg;
                while ((msg = bufferedReader.readLine()) == null)
                    ;
                jta.append(msg + "\n");
                sendMsg(msg);
                ParseMsg parseMsg = new ParseMsg(msg);
                // 根据用户名、聊天室名称、套接字创建用户聊天线程
                ChatThread tmp = new ChatThread(parseMsg.getSourse(), parseMsg.getTarget(), socket);
                // 线程开启
                tmp.start();
                // 向新用户发送服务器用户情况
                PrintStream printStream = new PrintStream(socket.getOutputStream());
                msg = ("UserName/");
                for (ChatThread i : chatThread) {
                    msg = msg + i.userName + "/";
                }
                printStream.println(msg);
                chatThread.add(tmp);
            } catch (IOException ioe) {
            }
        }
    }

    // 根据消息解析并按不同方式发送
    public void sendMsg(String msg) {
        ParseMsg parseMsg = new ParseMsg(msg);
        // 广播
        if (parseMsg.getMethod().equals("BROADCAST")) {
            broadcast(parseMsg.getMsg());
            // 群组
        } else if (parseMsg.getMethod().equals("GROUP")) {
            group(parseMsg.getTarget(), parseMsg.getMsg());
            // 点对点
        } else if (parseMsg.getMethod().equals("PTP")) {
            ptp(parseMsg.getTarget(), parseMsg.getMsg());
            // 用户退出
        } else if (parseMsg.getMethod().equals("LEAVE")) {
            for (ChatThread i : chatThread) {
                if (parseMsg.getSourse().equals(i.userName)) {
                    // 中断线程
                    i.interrupt();
                    // 从运行列表中移出
                    chatThread.remove(i);
                    try {
                        // 关闭输入流、输出流、套接字
                        i.bufferedReader.close();
                        i.printStream.close();
                        i.socket.close();
                        break;
                    } catch (IOException ioe) {
                        ioe.printStackTrace();
                    }
                }
            }
            // 广播用户离开信息
            broadcast(parseMsg.getMsg());
        }
    }

    // 广播
    public void broadcast(String msg) {
        for (ChatThread i : chatThread) {
            i.printStream.println(msg);
        }
    }

    // 群组
    public void group(String target, String msg) {
        for (ChatThread i : chatThread) {
            if (i.chatRoom.equals(target))
                i.printStream.println(msg);
        }
    }

    // 点对点
    public void ptp(String target, String msg) {
        for (ChatThread i : chatThread) {
            if (i.userName.equals(target)) {
                i.printStream.println(msg);
                break;
            }
        }
    }

    // 聊天线程类
    class ChatThread extends Thread {
        String userName = null;
        String chatRoom = null;
        Socket socket = null;
        BufferedReader bufferedReader = null;
        PrintStream printStream = null;

        public ChatThread(String userName, String chatRoom, Socket socket) {
            this.userName = userName;
            this.chatRoom = chatRoom;
            this.socket = socket;
            try {
                this.bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                this.printStream = new PrintStream(socket.getOutputStream());
            } catch (IOException ioe) {
                ioe.printStackTrace();
            }
        }

        // 线程运行内容
        public void run() {
            // 不断从输入流中获取信息
            while (true) {
                try {
                    String msg = bufferedReader.readLine();
                    if (msg != null && !msg.equals("")) {
                        jta.append(msg + "\n");
                        sendMsg(msg);
                    }
                } catch (Exception e) {
                }
            }
        }

    }

    public static void main(String[] args) throws Exception {
        new Server();
    }
}