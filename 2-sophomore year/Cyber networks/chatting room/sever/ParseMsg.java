// 解析信息类
public class ParseMsg
{
    private String method;
    private String target=null;
    private String sourse=null;
    private String msg=null;
    public ParseMsg(String msg)
    {
        this.method=msg.split("/")[0];
        this.sourse=msg.split("/")[1];
        this.target=msg.split("/")[2];
        this.msg=msg.split(msg.split("/")[2]+"/")[1];
        System.out.println(msg+"   "+this.getMsg());
    }
    // 获取信息类型
    public String getMethod()
    {
        return this.method;
    }
    // 获取信息发送方
    public String getSourse()
    {
        return this.sourse;
    }
    // 获取信息目标方
    public String getTarget()
    {
        return this.target;
    }
    // 获取信息内容
    public String getMsg()
    {
        return this.msg;
    }
}