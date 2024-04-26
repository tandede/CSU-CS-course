package chat;

import javax.swing.*;
//import com.sun.org.apache.bcel.internal.generic.NEW;
import java.awt.*;
import java.awt.event.*;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;

public class client extends JFrame implements Runnable,ActionListener {
    //north
    private JMenuBar jMenuBar = new JMenuBar();//创建菜单栏对象
    private JMenu jMenu = new JMenu("关于");//创建菜单对象，里面可包含菜单项
    private JMenuItem jMenuItemAbout = new JMenuItem("关于本软件");//菜单项
    private JMenuItem jMenuItemExit = new JMenuItem("退出");//菜单项
    JPanel jPanelNorth = new JPanel();
    //west
    JPanel jPanelWest = new JPanel();
    DefaultListModel<String> dlm = new DefaultListModel<String>();//用DefaultListModel类构造JList，修改dlm，JList会很快响应
    private JList<String> userJList = new JList<String>(dlm);//用来展示和选择
    JScrollPane jScrollPaneUJL = new JScrollPane(userJList);//可滚动
    //center
    JPanel jPanelCenter = new JPanel();
    JTextArea jTextAreaCenter = new JTextArea(10,20);//系统消息显示
    JScrollPane jScrollPaneCenter = new JScrollPane(jTextAreaCenter);
    JPanel operJPanelSendMessage = new JPanel();//发送消息的操作面板
    JLabel jLabelInput = new JLabel("请输入:");
    JTextField jTextFieldCenter = new JTextField(24);

    JButton jButtonfxx = new JButton("发消息");

    private JButton jButtonfsxx = new JButton("发送消息");
    private JButton jButtonsfxx = new JButton("私发消息");
    private BufferedReader bufferedReader = null;
    private PrintStream printStream = null;
    private String clientName = null;

    //私聊面板
    JTextArea jTextArea = new JTextArea(11,45);
    JScrollPane jScrollPaneSL = new JScrollPane(jTextArea);
    JTextField jTextField = new JTextField(25);
    String chatName = new String();

    double MAIN_FRAME_LOC_X;//父窗口x坐标
    double MAIN_FRAME_LOC_Y;//父窗口y坐标

    boolean FirstSecret = true;//是否第一次私聊
    String senderName=null;//私聊发送者的名字
    String receiverName=null;//私聊接收者的名字

    public client() throws Exception{
        //north 菜单栏
        jMenuBar.add(jMenu);
        jMenu.add(jMenuItemAbout);
        jMenu.add(jMenuItemExit);
        jMenuItemAbout.addActionListener(this);
        jMenuItemExit.addActionListener(this);
        BorderLayout bl = new BorderLayout();
        jPanelNorth.setLayout(bl);
        jPanelNorth.add(jMenuBar,BorderLayout.NORTH);
        add(jPanelNorth,BorderLayout.NORTH);

        //east 好友列表
        Dimension dim = new Dimension(100,150);
        jPanelWest.setPreferredSize(dim);//在使用了布局管理器后用setPreferredSize来设置窗口大小
        //Dimension dim2 = new Dimension(100,150);
        //listPane.setPreferredSize(dim2);
        BorderLayout bl2 = new BorderLayout();
        jPanelWest.setLayout(bl2);
        jPanelWest.add(jScrollPaneUJL,BorderLayout.CENTER);//显示好友列表
        add(jPanelWest,BorderLayout.EAST);
        userJList.setFont(new Font("隶书",Font.BOLD,18));

        //center 聊天消息框  发送消息操作面板
        jTextAreaCenter.setEditable(false);//消息显示框是不能编辑的
        jTextArea.setEditable(false);

        BorderLayout bl3 = new BorderLayout();
        jPanelCenter.setLayout(bl3);
        FlowLayout fl = new FlowLayout(FlowLayout.LEFT);
        operJPanelSendMessage.setLayout(fl);
        operJPanelSendMessage.add(jLabelInput);
        operJPanelSendMessage.add(jTextFieldCenter);
        operJPanelSendMessage.add(jButtonfsxx);
        operJPanelSendMessage.add(jButtonsfxx);
        jPanelCenter.add(jScrollPaneCenter,BorderLayout.CENTER);//jScrollPaneCenter是消息展示框JScrollPane
        jPanelCenter.add(operJPanelSendMessage,BorderLayout.SOUTH);
        add(jPanelCenter,BorderLayout.CENTER);

        jScrollPaneCenter.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);//需要时才显示滚动条

        //鼠标事件，点击
        jButtonfsxx.addActionListener(this);
        jButtonsfxx.addActionListener(this);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        //this.setAlwaysOnTop(true);

        clientName = JOptionPane.showInputDialog("用户名：");
        this.setTitle(clientName + "的聊天室");//设置聊天室的头部信息
        this.setSize(700,400);
        this.setVisible(true);

        Socket s = new Socket("127.0.0.1", 9999);//服务器的ip和端口
        bufferedReader = new BufferedReader(new InputStreamReader(s.getInputStream()));
        printStream = new PrintStream(s.getOutputStream());
        new Thread(this).start();//run()
        printStream.println("LOGIN#" + clientName);//发送登录信息，消息格式：LOGIN#nickName

        jTextFieldCenter.setFocusable(true);//设置焦点

        //键盘事件，实现当输完要发送的内容后，直接按回车键，实现发送
        //监听键盘相应的控件必须是获得焦点（focus）的情况下才能起作用
        jTextFieldCenter.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if(e.getKeyCode() == KeyEvent.VK_ENTER) {
                    printStream.println("MSG#" + clientName + "#" +  jTextFieldCenter.getText());//发送消息的格式：MSG#nickName#message
                    //发送完后，是输入框中内容为空
                    jTextFieldCenter.setText("");
                }
            }
        });

        //私聊消息框按回车发送消息
        jTextField.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if(e.getKeyCode() == KeyEvent.VK_ENTER) {
                    handleSS();
                }
            }
        });

        //监听系统关闭事件，退出时给服务器端发出指定消息
        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                printStream.println("OFFLINE#" + clientName);//发送下线信息，消息格式：OFFLINE#clientName
            }
        });

        this.addComponentListener(new ComponentAdapter() {//监听父窗口大小的改变
            public void componentMoved(ComponentEvent e) {
                Component comp = e.getComponent();
                MAIN_FRAME_LOC_X = comp.getX();
                MAIN_FRAME_LOC_Y = comp.getY();
            }
        });
    }

    public void run(){//客户端与服务器端发消息的线程
        while (true){
            try{
                String msg = bufferedReader.readLine();//读取服务器是否发送了消息给该客户端
                String[] strs = msg.split("#");//分隔符为#
                //判断是否为服务器发来的登陆信息
                if(strs[0].equals("LOGIN")){
                    if(!strs[1].equals(clientName)){//不是本人的上线消息就显示，本人的不显示
                        jTextAreaCenter.append(strs[1] + "上线啦！快去找他聊天叭\n");
                        dlm.addElement(strs[1]);//DefaultListModel来更改JList的内容
                        userJList.repaint();//更新
                    }
                }else if(strs[0].equals("MSG")){//接到服务器发送消息的信息
                    if(!strs[1].equals(clientName)){//别人说的
                        jTextAreaCenter.append(strs[1] + "说：" + strs[2] + "\n");
                    }else{
                        jTextAreaCenter.append("我说：" + strs[2] + "\n");
                    }
                }else if(strs[0].equals("USERS")){//USER消息，为新建立的客户端更新好友列表
                    dlm.addElement(strs[1]);
                    userJList.repaint();
                } else if(strs[0].equals("ALL")){
                    jTextAreaCenter.append("系统消息：" + strs[1] + "\n");
                }else if(strs[0].equals("OFFLINE")){
                    if(strs[1].equals(clientName)) {//如果是自己下线的消息，说明被服务器端踢出聊天室，强制下线
                        javax.swing.JOptionPane.showMessageDialog(this, "您已被系统请出聊天室！");
                        System.exit(0);//退出程序
                    }
                    jTextAreaCenter.append(strs[1] + "下线啦！\n");
                    dlm.removeElement(strs[1]);//更新好友列表
                    userJList.repaint();
                }else if((strs[2].equals(clientName) || strs[1].equals(clientName)) && strs[0].equals("SMSG")){
                    if(!strs[1].equals(clientName)){
                        jTextArea.append(strs[1] + "说：" + strs[3] + "\n");
                        jTextAreaCenter.append("系统提示：" + strs[1] + "私信了你" + "\n");
                    }else{
                        jTextArea.append("我说：" + strs[3] + "\n");
                    }
                }else if((strs[2].equals(clientName) || strs[1].equals(clientName)) && strs[0].equals("FSMSG"))
                {
                    senderName = strs[1];
                    receiverName = strs[2];
                    //接收方第一次收到私聊消息，自动弹出私聊窗口
                    if(!strs[1].equals(clientName)) {
                        FirstSecret = false;
                        jTextArea.append(strs[1] + "说：" + strs[3] + "\n");
                        jTextAreaCenter.append("系统提示：" + strs[1] + "私信了你" + "\n");
                        handleSec(strs[1]);
                    }
                    else {
                        jTextArea.append("我说：" + strs[3] + "\n");
                    }
                }
            }catch (Exception ex){//如果服务器端出现问题，则客户端强制下线
                javax.swing.JOptionPane.showMessageDialog(this, "您已被系统请出聊天室！");
                System.exit(0);
            }
        }
    }


    @Override
    public void actionPerformed(ActionEvent e) {//鼠标点击事件
        String label = e.getActionCommand();
        if(label.equals("发送消息")){//群发
            handleSend();
        }else if(label.equals("私发消息") && !userJList.isSelectionEmpty()){//未点击用户不执行
            chatName = userJList.getSelectedValuesList().get(0);//获得被选择的用户
            handleSec(chatName);//创建私聊窗口
            senderName = clientName;
            receiverName = chatName;
        }else if(label.equals("发消息")){
            handleSS();//私发消息
        }else if(label.equals("关于本软件")){
            JOptionPane.showMessageDialog(this, "1.可以在聊天框中进行群聊\n\n2.可以点击选择用户进行私聊");
        }else if(label.equals("退出")){
            JOptionPane.showMessageDialog(this, "您已成功退出！");
            printStream.println("OFFLINE#" + clientName);
            System.exit(0);
        } else{
            System.out.println("不识别的事件");
        }
    }

    public void handleSS(){//在私聊窗口中发消息
        String name=senderName;
        if(senderName.equals(clientName)) {
            name = receiverName;
        }
        if(FirstSecret) {
            printStream.println("FSMSG#" + clientName + "#" + name + "#" + jTextField.getText());
            jTextField.setText("");
            FirstSecret = false;
        }
        else {
            printStream.println("SMSG#" + clientName + "#" + name + "#" + jTextField.getText());
            jTextField.setText("");
        }
    }

    public void handleSend(){//群发消息
        //发送信息时标识一下来源
        printStream.println("MSG#" + clientName + "#" +  jTextFieldCenter.getText());
        //发送完后，是输入框中内容为空
        jTextFieldCenter.setText("");
    }

    public void handleSec(String name){ //建立私聊窗口
        JFrame.setDefaultLookAndFeelDecorated(true);
        JFrame jFrame = new JFrame();//新建了一个窗口
        JPanel JPL = new JPanel();
        JPanel JPL2 = new JPanel();
        FlowLayout f2 = new FlowLayout(FlowLayout.LEFT);
        JPL.setLayout(f2);
        JPL.add(jTextField);
        JPL.add(jButtonfxx);
        JPL2.add(jScrollPaneSL,BorderLayout.CENTER);
        JPL2.add(JPL,BorderLayout.SOUTH);
        jFrame.add(JPL2);

        jButtonfxx.addActionListener(this);
        jTextArea.setFont(new Font("宋体", Font.PLAIN,15));
        jFrame.setSize(400,310);
        jFrame.setLocation((int)MAIN_FRAME_LOC_X+20,(int)MAIN_FRAME_LOC_Y+20);//将私聊窗口设置总是在父窗口的中间弹出
        jFrame.setTitle("与" + name + "私聊中");
        jFrame.setVisible(true);

        jTextField.setFocusable(true);//设置焦点

        jFrame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                jTextArea.setText("");
                FirstSecret = true;
            }
        });
    }//私聊窗口

    public static void main(String[] args)throws Exception{
        JFrame.setDefaultLookAndFeelDecorated(true);
        new client();
    }
}


