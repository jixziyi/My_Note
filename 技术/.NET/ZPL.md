# ZPL 转换核心代码

``` CSharp
public partial class ZplPrintControl
{
    public string ZPL_Start()
    {
        StringBuilder builder = new StringBuilder();
        builder.AppendLine("^XA"); //指令块的开始  
        builder.AppendLine("^MMC,Y");
        builder.AppendLine("^PRE,E");
        builder.AppendLine("^MD30"); //MD是设置色带颜色的深度  

        builder.AppendLine("^LH0,0");
        builder.AppendLine("^ABN,50,50");
        builder.AppendLine("^CW1,D:MSUNG.FNT");
        builder.AppendLine("^SEE:GB8BIT.DAT");
        builder.AppendLine("^CI26");

        return builder.ToString();
    }

    public string ZPL_End()
    {
        StringBuilder builder = new StringBuilder();

        builder.AppendLine("^XZ"); //指令块的结束  
        return builder.ToString();
    }

    /// <summary>  
    ///  设置打印标签纸边距  
    /// </summary>  
    /// <param name="printX">标签纸边距x坐标</param>  
    /// <param name="printY">标签纸边距y坐标</param>  
    /// <returns></returns>  
    public string ZPL_PageSet(int printX, int printY)
    {
        StringBuilder builder = new StringBuilder();
        builder.AppendLine("^LH" + printX + "," + printY); //定义条码纸边距  80 10  
        return builder.ToString();
    }

    /// <summary>  
    /// 打印凭条设置  
    /// </summary>  
    /// <param name="width">凭条宽度</param>  
    /// <param name="height">凭条高度</param>  
    /// <returns>返回ZPL命令</returns>  
    public string ZPL_SetLabel(int width, int height)
    {
        //ZPL条码设置命令：^PW640^LL480  
        string sReturn = "^PW{0}^LL{1}";
        return string.Format(sReturn, width, height);
    }

    /// <summary>  
    ///  打印矩形  
    /// </summary>  
    /// <param name="px">起点X坐标</param>  
    /// <param name="py">起点Y坐标</param>  
    /// <param name="thickness">边框宽度</param>  
    /// <param name="width">矩形宽度，0表示打印一条竖线</param>  
    /// <param name="height">矩形高度，0表示打印一条横线</param>  
    /// <returns>返回ZPL命令</returns>  
    public string ZPL_DrawRectangle(int px, int py, int thickness, int width, int height)
    {
        //ZPL矩形命令：^FO50,50^GB300,200,2^FS  
        string sReturn = "^FO{0},{1}^GB{3},{4},{2}^FS";
        return string.Format(sReturn, px, py, thickness, width, height);
    }

    /// <summary>  
    /// 打印英文  
    /// </summary>  
    /// <param name="EnText">待打印文本</param>  
    /// <param name="ZebraFont">打印机字体 A-Z</param>  
    /// <param name="px">起点X坐标</param>  
    /// <param name="py">起点Y坐标</param>  
    /// <param name="Orient">旋转角度N = normal，R = rotated 90 degrees (clockwise)，I = inverted 180 degrees，B = read from bottom up, 270 degrees</param>  
    /// <param name="Height">字体高度</param>  
    /// <param name="Width">字体宽度</param>  
    /// <returns>返回ZPL命令</returns>  
    public string ZPL_DrawENText(string EnText, string ZebraFont, int px, int py, string Orient, int Height, int Width)
    {
        //ZPL打印英文命令：^FO50,50^A0N,32,25^FDZEBRA^FS  
        string sReturn = "^FO{1},{2}^A" + ZebraFont + "{3},{4},{5}^FD{0}^FS";
        return string.Format(sReturn, EnText, px, py, Orient, Height, Width);
    }


    /// <summary>  
    /// 中文处理,返回ZPL命令  
    /// </summary>  
    /// <param name="ChineseText">待转变中文内容</param>  
    /// <param name="FontName">字体名称</param>  
    /// <param name="startX">X坐标</param>  
    /// <param name="startY">Y坐标</param>  
    /// <param name="Orient">旋转角度0,90,180,270</param>  
    /// <param name="Height">字体高度</param>  
    /// <param name="Width">字体宽度，通常是0</param>  
    /// <param name="IsBold">1 变粗,0 正常</param>  
    /// <param name="IsItalic">1 斜体,0 正常</param>  
    /// <returns></returns>  
    public string ZPL_DrawCHText(string ChineseText, string FontName, int startX, int startY, int Orient, int Height, int Width, int IsBold, int IsItalic)
    {
        StringBuilder sResult = new StringBuilder();
        StringBuilder hexbuf = new StringBuilder(21 * 1024);
        int count = ZplPrintControl.GETFONTHEX(ChineseText, FontName, Orient, Height, Width, IsBold, IsItalic, hexbuf);
        if (count > 0)
        {
            string sEnd = "^FO" + startX.ToString() + "," + startY.ToString() + "^XGOUTSTR" + ",1,2^FS ";
            sResult.AppendLine(hexbuf.ToString().Replace("OUTSTR01", "OUTSTR") + sEnd);
        }
        return sResult.ToString();
    }

    /// <summary>  
    /// 打印条形码（128码）  
    /// </summary>  
    /// <param name="px">起点X坐标</param>  
    /// <param name="py">起点Y坐标</param>  
    /// <param name="width">基本单元宽度 1-10</param>  
    /// <param name="ratio">宽窄比 2.0-3.0 增量0.1</param>  
    /// <param name="barheight">条码高度</param>  
    /// <param name="barcode">条码内容</param>  
    /// <returns>返回ZPL命令</returns>  
    public string ZPL_DrawBarcode(int px, int py, int width, int ratio, int barheight, string barcode)
    {
        //ZPL打印英文命令：^FO50,260^BY1,2^BCN,100,Y,N^FDSMJH2000544610^FS  
        string sReturn = "^FO{0},{1}^BY{2},{3}^BCN,{4},N,N^FD{5}^FS";
        return string.Format(sReturn, px, py, width, ratio, barheight, barcode);
    }

    /// <summary>
    /// 打印二维码
    /// </summary>
    /// <param name="px"></param>
    /// <param name="py"></param>
    /// <param name="cl"></param>
    /// <param name="bch"></param>
    /// <param name="qrCode"></param>
    /// <returns></returns>
    public string ZPL_DrawQRCode(int px, int py, int cl, int bch, string qrCode)
    {
        StringBuilder sb = new StringBuilder();
        sb.AppendFormat("^FO{0},{1}", px, py);
        sb.Append("^BQ,2,7");
        sb.AppendFormat("^FDLA,{0}^FS", qrCode);

        return sb.ToString();
    }
}
```