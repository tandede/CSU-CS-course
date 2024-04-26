import javax.swing.*;
import java.awt.*;

/**
 * @author wzs
 *
 * 爬取操作的弹窗展示
 */
class ProgressBar extends JDialog {

    private static final long serialVersionUID = 1L;

    /**
     * 弹出的对话框中的主画布
     */
    private final JPanel jPanel = new JPanel();

    /**
     * 进度条展示
     */
    private final JProgressBar jProgressBar = new JProgressBar();

    /**
     * 显示当前被爬取的网址信息
     */
    private final JLabel siteLabel = new JLabel();

    /**
     * 进度条窗口展示格式初始化
     */
    public ProgressBar(JFrame jFrame, String title) {
        super(jFrame, title);
        this.setLocation(jFrame.getWidth() / 2 + (int) jFrame.getLocation().getX() / 2 - 80, jFrame.getHeight() / 2 + (int) jFrame.getLocation().getY() / 2 - 30);
        this.setSize(400, 100);
        this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);

        jPanel.setLayout(new BorderLayout());
        jProgressBar.setString("玩命加载中...");
        jProgressBar.setIndeterminate(true); // 设置进度条为不确定模式
        jProgressBar.setStringPainted(true);
        jProgressBar.setBorderPainted(false);
        jProgressBar.setForeground(Color.RED); // 设置进度条颜色
        jProgressBar.setBackground(Color.WHITE); // 设置背景
        siteLabel.setPreferredSize(new Dimension(400, 30));

        // 界面布局
        jPanel.add(siteLabel, BorderLayout.NORTH);
        jPanel.add(jProgressBar, BorderLayout.CENTER);
        this.add(jPanel);
    }

    /**
     * 设置当前对话框的界面标题
     */
    public void setText(String text) {
        siteLabel.setText(text);
    }
}
