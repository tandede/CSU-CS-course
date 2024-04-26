import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.Socket;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;

// 用户登录界面类
public class UserLogin extends JFrame implements ActionListener {
    private String UserName = null;
    private String chatRoom = null;
    private JLabel jl1 = new JLabel("请输入用户名:");
    private JTextField jtf1 = new JTextField();
    private JLabel jl2 = new JLabel("请输入聊天室:");
    private JTextField jtf2 = new JTextField();
    private Socket socket;
    private JButton jb = new JButton("确定");
    private JLabel jle = new JLabel();

    public UserLogin() {
        this.setTitle("登录");
        this.setSize(420, 400);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setVisible(true);
        this.setLayout(null);
        jl1.setBounds(80, 100, 120, 20);
        this.add(jl1);
        jl2.setBounds(80, 150, 120, 20);
        this.add(jl2);
        jtf1.setBounds(200, 100, 120, 20);
        jtf1.addActionListener(this);
        this.add(jtf1);
        jtf2.setBounds(200, 150, 120, 20);
        jtf2.addActionListener(this);
        this.add(jtf2);
        jb.setBounds(160, 180, 80, 20);
        jb.addActionListener(this);
        this.add(jb);
        jle.setBounds(180, 200, 120, 20);
        this.add(jle);
    }

    public void actionPerformed(ActionEvent e) {
        // 获取用户名
        this.UserName = jtf1.getText();
        // 获取聊天室名
        this.chatRoom = jtf2.getText();
        if (!this.UserName.equals("") && !this.chatRoom.equals("")) {
            try {
                // 创建套接字
                socket = new Socket("127.0.0.1", 8080);
                // 登录界面关闭窗口
                this.dispose();
                // 实例化用户类
                new Client(this.UserName, this.chatRoom, this.socket);
            } catch (Exception ex) {
                jle.setText("连接失败，请重试!");
            }
        } else {
            jle.setText("请重新输入!");
        }
    }

    public static void main(String[] args) {
        new UserLogin();
    }
}