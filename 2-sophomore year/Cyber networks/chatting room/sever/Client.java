import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowListener;
import java.awt.event.WindowEvent;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;

import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JTextArea;
import javax.swing.JTextField;

// 用户类
public class Client extends JFrame implements Runnable, ActionListener, WindowListener {
    private String userName;
    private String chatRoom;
    private Socket socket;
    private PrintStream ps = null;
    private BufferedReader bf = null;
    private JTextField jtf = new JTextField();
    private JTextArea jta = new JTextArea();
    private JComboBox<String> jcb = new JComboBox<String>(new String[] { "Server" });

    public Client(String userName, String chatRoom, Socket socket) throws Exception {
        this.userName = userName;
        this.chatRoom = chatRoom;
        jcb.addItem(this.chatRoom);
        this.setTitle(userName + "-已连接");
        this.setSize(400, 400);
        this.setDefaultCloseOperation(HIDE_ON_CLOSE);
        this.setVisible(true);
        this.add(jtf, BorderLayout.SOUTH);
        this.add(jta, BorderLayout.CENTER);
        this.add(jcb, BorderLayout.NORTH);
        bf = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        ps = new PrintStream(socket.getOutputStream());
        ps.println("BROADCAST/" + userName + "/" + chatRoom + "/" + userName + "已进入" + chatRoom + "\n");
        jtf.addActionListener(this);
        this.addWindowListener(this);
        new Thread(this).start();
    }

    // 根据发送方法发送信息
    public void sendmsg(String msg) {
        if (jcb.getSelectedItem().equals("Server")) {
            ps.println("BROADCAST/" + userName + "/Server/" + msg);
        } else if (jcb.getSelectedItem().equals(this.chatRoom)) {
            ps.println("GROUP/" + userName + "/" + this.chatRoom + "/" + msg);
        } else {
            ps.println("PTP/" + userName + "/" + jcb.getSelectedItem() + "/" + msg);
        }
    }

    // 线程运行内容
    public void run() {
        while (true) {
            try {
                String msg = bf.readLine();
                // 新用户进入聊天室
                if (msg.indexOf("已进入") != -1) {
                    jcb.addItem(msg.split("已进入")[0]);
                    jta.append(msg + "\n");
                    // 用户离开聊天室
                } else if (msg.indexOf("已离开") != -1) {
                    jcb.removeItem(msg.split("已离开")[0]);
                    jta.append(msg + "\n");
                    // 接收已经在聊天室的用户信息
                } else if (msg.startsWith("UserName")) {
                    String[] parse = msg.split("/");
                    for (int i = 1; i < parse.length; i++) {
                        jcb.addItem(parse[i]);
                    }
                } else {
                    jta.append(msg + "\n");
                }
            } catch (Exception e) {
            }
        }
    }

    // 如果发送信息，根据下拉列表框内容确定发送方式
    public void actionPerformed(ActionEvent e) {
        String msg = new String(this.userName + "对");
        if (jcb.getSelectedItem().equals("Server")) {
            msg += "所有人说：";
        } else if (jcb.getSelectedItem().equals(this.chatRoom)) {
            msg += "聊天室" + this.chatRoom + "中的所有人说：";
        } else {
            msg += jcb.getSelectedItem() + "说：";
        }
        if (!jcb.getSelectedItem().equals("Server") && !jcb.getSelectedItem().equals(this.chatRoom)) {
            jta.append(msg + ":" + jtf.getText() + "\n");
        }
        sendmsg(msg + jtf.getText() + "\n");
        jtf.setText("");
    }

    public void windowActivated(WindowEvent e) {

    }

    // 如果窗口关闭，则发送用户离开信息
    public void windowClosing(WindowEvent e) {
        ps.println("LEAVE/" + this.userName + "/" + this.chatRoom + "/" + this.userName + "已离开" + this.chatRoom + "\n");
        this.ps.close();
        try {
            this.bf.close();
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
        this.dispose();
        System.exit(0);
    }

    public void windowClosed(WindowEvent e) {

    }

    public void windowIconified(WindowEvent e) {

    }

    public void windowOpened(WindowEvent e) {

    }

    public void windowDeiconified(WindowEvent e) {

    }

    public void windowDeactivated(WindowEvent e) {
    }

}