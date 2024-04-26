import javax.swing.*;
import javax.swing.text.BadLocationException;
import javax.swing.text.DefaultHighlighter.DefaultHighlightPainter;
import javax.swing.text.Highlighter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @author wzs
 *
 * 用 JavaURL 编程爬取并分析网页敏感词
 */
public class SpiderFrame extends JFrame implements ActionListener {

    private final JPanel jPanel1 = new JPanel();

    private final JPanel jPanel2 = new JPanel();

    private final JPanel jPanel3 = new JPanel();

    private final JPanel jPanel4 = new JPanel();

    private final JPanel jPanel5 = new JPanel();

    private final JPanel jPanel6 = new JPanel();

    private final JPanel jPanel7 = new JPanel();

    private final JPanel jPanel8 = new JPanel();

    private final JPanel jPanel9 = new JPanel();

    /**
     * 输入网址标签即接收输入的文本框
     */
    private final JLabel siteLabel = new JLabel("输入网址:");

    private final JTextField siteField = new JTextField(25);

    private final JScrollPane siteScrollPane = new JScrollPane(siteField);

    /**
     * 开始爬取按钮
     */
    private final JButton startButton = new JButton("开始爬取");

    /**
     * 存储爬取到的 html 源码的文本域，并将其放入一个 JScrollPane 中
     */
    private final JTextArea htmlArea = new JTextArea(15, 25);

    private final JScrollPane htmlScrollPane = new JScrollPane(htmlArea);

    /**
     * 存储爬到的网页的文本信息，并将其放入一个 JScrollPane 中
     */
    private final JTextArea textArea = new JTextArea(15, 25);

    private final JScrollPane textScrollPane = new JScrollPane(textArea);

    /**
     * 选择展示爬取到的 html 源码或者网页文本的标签栏
     */
    private final JTabbedPane tabPane = new JTabbedPane();

    /**
     * 展示敏感词的文本域，并存入一个 JScrollPane 中进行展示
     */
    private final JTextArea wordTextArea = new JTextArea(8, 25);

    private final JScrollPane wordScrollPane = new JScrollPane(wordTextArea);

    /**
     * 存储敏感词的 list
     */
    private final ArrayList<String> wordList = new ArrayList<>();

    /**
     * 存储每个敏感词的出现次数
     */
    private final ArrayList<Integer> wordNum = new ArrayList<>();

    /**
     * 导入敏感词库按钮
     */
    private final JButton importWordButton = new JButton("导入敏感词库");

    /**
     * 匹配按钮
     */
    private final JButton matchButton = new JButton("匹配");

    /**
     * 导入网址库按钮
     */
    private final JButton importUrlButton = new JButton("导入网址库");

    /**
     * 可以选择字符集的下拉框
     */
    private final JComboBox<String> charset = new JComboBox<>();

    private String textType = "UTF-8";

    /**
     * 匹配标签
     */
    private final String regExTag = "<[^>]+>";

    /**
     * 匹配 script 标签
     */
    private final String regExScript = "<script[^>]*?>[\\s\\S]*?</script>";

    /**
     * 匹配 style 标签
     */
    private final String regExStyle = "<style[^>]*?>[\\s\\S]*?</style>";

    /**
     * 匹配连续空格或回车等
     */
    private final String regExSpace = "\\s{2,}";

    /**
     * 匹配网页上图案的乱码
     */
    private final String regExImg = "&\\S*?;+";

    /**
     * 根据正则串创建对应的模式对象
     */
    private final Pattern patternTag = Pattern.compile(regExTag, Pattern.CASE_INSENSITIVE);

    private final Pattern patternScript = Pattern.compile(regExScript, Pattern.CASE_INSENSITIVE);

    private final Pattern patternStyle = Pattern.compile(regExStyle, Pattern.CASE_INSENSITIVE);

    private final Pattern patternSpace = Pattern.compile(regExSpace, Pattern.CASE_INSENSITIVE);

    private final Pattern patternImg = Pattern.compile(regExImg, Pattern.CASE_INSENSITIVE);

    public SpiderFrame() {
        // 设置界面风格
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            e.printStackTrace();
        }
        this.setTitle("Spider");
        this.setLocation(400, 200);
        this.setSize(600, 500);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setVisible(true);

        // 为字符集下拉框添加选项并绑定事件，默认为 utf-8
        charset.addItem("UTF-8");
        charset.addItem("GBK");
        charset.setEditable(false);
        charset.addActionListener(e -> textType = (String) charset.getSelectedItem());

        // 1、界面的最上面一栏，界面处理，提醒输入网址，爬取按钮，以及编码方式选择
        jPanel2.setLayout(new BorderLayout());
        siteLabel.setPreferredSize(new Dimension(70, 30));
        siteScrollPane.setPreferredSize(new Dimension(300, 30));
        startButton.setPreferredSize(new Dimension(90, 30));
        jPanel3.setLayout(new GridLayout(1, 2, 10, 10));
        jPanel3.add(startButton);
        startButton.addActionListener(this);
        jPanel3.add(charset);
        jPanel2.add(siteLabel, BorderLayout.WEST);
        jPanel2.add(siteScrollPane, BorderLayout.CENTER);
        jPanel2.add(jPanel3, BorderLayout.EAST);

        // 2、界面的中下部分
        // 2.1、界面中下部分中的最右边一列
        jPanel6.setLayout(new BorderLayout());
        wordTextArea.setLineWrap(true);
        wordTextArea.setEditable(false);
        jPanel5.setLayout(new GridLayout(2, 1, 10, 5));
        jPanel5.add(importUrlButton);
        importUrlButton.addActionListener(this);
        jPanel5.add(importWordButton);
        importWordButton.addActionListener(this);
        wordScrollPane.setPreferredSize(new Dimension(6, 400));
        jPanel6.add(jPanel5, BorderLayout.NORTH);
        jPanel6.add(wordScrollPane, BorderLayout.CENTER);
        jPanel6.add(matchButton, BorderLayout.SOUTH);
        matchButton.addActionListener(this);

        // 2.2、页面中间部分，html 源代码以及网页文本展示
        htmlArea.setEditable(false);
        htmlArea.setLineWrap(true); // 设置自动换行策略
        htmlArea.setFont(new Font("宋体", Font.PLAIN, 14));
        jPanel4.setLayout(new BorderLayout());
        jPanel4.add(htmlScrollPane, BorderLayout.CENTER);
        textArea.setEditable(false);
        textArea.setLineWrap(true);
        textArea.setFont(new Font("宋体", Font.PLAIN, 14));
        jPanel7.setLayout(new BorderLayout());
        jPanel7.add(textScrollPane, BorderLayout.CENTER);
        tabPane.add("html源代码", jPanel4);
        tabPane.add("网页文本", jPanel7);
        jPanel8.setLayout(new BorderLayout());
        jPanel8.add(tabPane, BorderLayout.CENTER);

        // 2.3、整合页面的中下部分
        jPanel9.setLayout(new BorderLayout());
        jPanel9.add(jPanel8, BorderLayout.CENTER);
        jPanel9.add(jPanel6, BorderLayout.EAST);

        jPanel1.setLayout(new BorderLayout());
        jPanel1.add(jPanel2, BorderLayout.NORTH);
        jPanel1.add(jPanel9, BorderLayout.CENTER);
        this.add(jPanel1);
    }

    /**
     * 爬取指定 url 的 html 源码
     * @param siteUrl 待爬取的 url
     */
    public String getHtml(String siteUrl) {
        StringBuilder text = new StringBuilder(); // 保存网页的内容
        try {
            URL url = new URL(siteUrl); // 建立对应的 url 对象
            URLConnection urlConnection = url.openConnection(); // 获取 url 的连接对象
            urlConnection.connect(); // 连接对应的 url
            // 获取该连接对应的输入流
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(urlConnection.getInputStream(), textType));
            System.out.println("开始爬取");
            while (true) { // 爬取到结束
                String str = bufferedReader.readLine();
                if (str == null) break;
                text.append(str).append("\n");
            }
            bufferedReader.close();
        } catch (Exception e) {
            JOptionPane.showMessageDialog(null, siteUrl + " 爬取源代码失败");
        }
        System.out.println("爬取结束");
        return text.toString(); // 返回 html 代码文本
    }

    /**
     * 对 html 源码进行正则匹配，提取出其中的文本
     */
    public String getText(String htmlStr) {
        Matcher matcher = patternScript.matcher(htmlStr);
        htmlStr = matcher.replaceAll("");
        matcher = patternStyle.matcher(htmlStr);
        htmlStr = matcher.replaceAll("");
        matcher = patternTag.matcher(htmlStr);
        htmlStr = matcher.replaceAll("");
        matcher = patternSpace.matcher(htmlStr);
        htmlStr = matcher.replaceAll("\n");
        matcher = patternImg.matcher(htmlStr);
        htmlStr = matcher.replaceAll("");
        return htmlStr;
    }

    /**
     * 从文件中导入敏感词
     */
    public void importWordMethod() {
        JFileChooser fChooser = new JFileChooser(); // 文件选择框
        if (fChooser.showOpenDialog(this) != JFileChooser.APPROVE_OPTION) return; // 判断是否正常选择
        // 清空旧记录
        wordList.clear();
        wordTextArea.setText("");
        File selectedFile = fChooser.getSelectedFile(); //获取选择的文件
        BufferedReader bufferedReader;
        try { // 读取选中文件中的记录
            bufferedReader = new BufferedReader(new FileReader(selectedFile));
            while (true) {
                String str = bufferedReader.readLine();
                if (str == null) break;
                wordList.add(str); // 添加到记录中
                wordNum.add(0); // 设置对应的初始值
                wordTextArea.append(str + "\n"); // 添加到界面中
            }
            bufferedReader.close(); // 关闭文件流
        } catch (FileNotFoundException e1) {
            JOptionPane.showMessageDialog(null, "文件不存在");
            e1.printStackTrace();
        } catch (IOException e1) {
            JOptionPane.showMessageDialog(null, "文件读取失败");
            e1.printStackTrace();
        }
    }

    /**
     * 高亮显示敏感词
     */
    public void showSensitiveWord() {
        Highlighter highlighter = textArea.getHighlighter(); // 设置文本框的高亮显示
        highlighter.removeAllHighlights(); // 清除之前的高亮显示记录
        String text = textArea.getText(); // 得到文本框的文本
        DefaultHighlightPainter painter = new DefaultHighlightPainter(Color.YELLOW); // 设置高亮显示颜色为黄色
        for (String word : wordList) { // 匹配其中的每一个敏感词
            int index = 0;
            while ((index = text.indexOf(word, index)) >= 0) {
                try {
                    highlighter.addHighlight(index, index + word.length(), painter); // 高亮显示匹配到的词语
                    index += word.length(); // 更新匹配条件继续匹配
                } catch (BadLocationException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    /**
     * 爬取网址库中的所有网址
     */
    public void spiderAll() {
        if (wordNum.size() <= 0) { // 判断是否选择了敏感词库
            JOptionPane.showMessageDialog(null, "请先选择敏感词库");
            return;
        }
        JFileChooser fChooser = new JFileChooser(); // 选择存储网址库的文件
        if (fChooser.showOpenDialog(this) != JFileChooser.APPROVE_OPTION) return;
        File siteLabFile = fChooser.getSelectedFile();
        new SpiderAll(this, siteLabFile).start(); // 开启线程爬取
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        JButton button = (JButton) e.getSource(); // 获取事件来源
        if (button == startButton) { // 爬取单个网址
            String siteUrl = siteField.getText();
            new SpiderOne(this, siteUrl).start();
        } else if (button == importWordButton) { // 打开敏感词库
            importWordMethod();
        } else if (button == matchButton) { // 匹配单个网址的敏感词高亮显示
            showSensitiveWord();
        } else if (button == importUrlButton) { // 爬取网址库中的全部网址
            spiderAll();
        }
    }

    public static void main(String[] args) {
        new SpiderFrame();
    }

    /**
     * 爬取单个网站的线程
     */
    class SpiderOne extends Thread {

        /**
         * 待爬取的网页 url
         */
        private final String siteUrl;

        /**
         * 爬取过程中展示的进度条组件
         */
        private final ProgressBar progressBar;

        /**
         * @param jFrame 父 frame
         * @param siteUrl 待爬取的网址 url
         */
        public SpiderOne(JFrame jFrame, String siteUrl) {
            this.siteUrl = siteUrl;
            progressBar = new ProgressBar(jFrame, "Spiding");
        }

        public void run() {
            if (siteUrl.length() <= 0) { // 判断网址是否正常
                JOptionPane.showMessageDialog(null, "网址不能为空");
                return;
            }
            // 将展示 html 源码和网页文本的文本域置空
            htmlArea.setText("");
            textArea.setText("");
            progressBar.setText("爬取" + siteUrl + "中..."); // 设置进度条界面标题
            progressBar.setVisible(true); // 显示进度条
            String html = getHtml(siteUrl); // 开始爬取
            progressBar.dispose(); // 关闭进度条
            if (html.length() > 0) { // 若爬取正常
                JOptionPane.showMessageDialog(null, "爬取完毕");
                htmlArea.append(html); // 显示 html 源代码
                String text = getText(html); //匹配网页文本
                textArea.append(text); //显示网页文本
            }
        }
    }

    /**
     * 爬取网址库
     */
    class SpiderAll extends Thread {
        private final File siteLabFile; // 网址库文本文件
        private final ProgressBar progressBar; // 进度条

        public SpiderAll(JFrame jFrame, File siteLibFile) {
            siteLabFile = siteLibFile;
            progressBar = new ProgressBar(jFrame, "Spiding");
        }

        public void run() {
            try {
                BufferedReader bufferedReader = new BufferedReader(new FileReader(siteLabFile));
                // 将匹配数据写入文本中
                PrintStream printStream = new PrintStream("data.txt");
                printStream.println("敏感词记录如下:");
                int size = wordList.size();
                progressBar.setVisible(true); // 显示进度条
                while (true) {
                    String siteUrl = bufferedReader.readLine();
                    if (siteUrl == null) break;
                    progressBar.setText("爬取" + siteUrl + "中..."); // 设置进度条界面标题
                    printStream.println(siteUrl + "数据如下: ");
                    String html = getHtml(siteUrl); // 获取 html 代码
                    String text = getText(html); // 匹配网页文本
                    for (int i = 0; i < size; i++) { // 在网页文本中进行匹配
                        String word = wordList.get(i);
                        int index = 0, count = 0, len = word.length();
                        while ((index = text.indexOf(word, index)) >= 0) {
                            count++;
                            int temp = wordNum.get(i); // 更新数据
                            wordNum.set(i, ++temp);
                            index += len; // 更新匹配条件
                        }
                        printStream.println(word + "  出现  " + count + "次"); // 写入当前数据
                    }
                    printStream.println();
                }
                bufferedReader.close(); // 关闭文件流
                System.out.println("爬取完毕");
                printStream.println("总数据如下:     "); // 写入总数据
                for (int i = 0; i < size; i++) {
                    printStream.println(wordList.get(i) + "  出现    " + wordNum.get(i) + "次");
                }
                printStream.close();
                JOptionPane.showMessageDialog(null, "爬取完毕！请打开文件查看!");
            } catch (Exception e) {
                JOptionPane.showMessageDialog(null, "爬取失败");
            } finally {
                progressBar.dispose(); // 关闭进度条
            }
        }
    }
}