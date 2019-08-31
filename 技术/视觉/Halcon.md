# Halcon

## 标定

### 找圆
``` VB
dev_close_window ()


read_image (Image1, 'C:/Users/guo/Desktop/机器视觉/pic/主板/正集源/2018-02-05_21-56-50-7570.bmp')
rgb1_to_gray (Image1, GrayImage)


dev_open_window_fit_image (Image1, 0, 0, -1, -1, WindowHandle)
set_display_font (WindowHandle, 16, 'mono', 'true', 'false')

dev_display (Image1)

scale_image (Image1, ImageScaled, 1.2, 0)
median_image (ImageScaled, ImageMedian, 'circle', 1, 'mirrored')

draw_rectangle1 (WindowHandle, Row1, Column1, Row2, Column2)
gen_rectangle1 (Rectangle, Row1, Column1, Row2, Column2)
reduce_domain (ImageMedian, Rectangle, ImageReduced)


' 阈值分割，定义目标对象阈值
threshold (ImageReduced, Regions, 200, 255)

' 连接区域
connection (Regions, ConnectedRegions)

' 根据区域大小查找 Shape
select_shape (ConnectedRegions, SelectedRegions, 'area', 'and', 10000, 54000)

' overpaint_region(ImageReduced, SelectedRegions, 255, 'fill')

' 填充区域
fill_up (SelectedRegions, RegionFillUp)

' 圆度判断
select_shape (RegionFillUp, SelectedRegions1, 'circularity', 'and', 0.8, 1)
' paint_gray (GrayImage, GrayImage, SelectedRegions)
' paint_region (SelectedRegions1, GrayImage, ImageRegion, 64, 'fill')

' 查找区域中心坐标
area_center (SelectedRegions1, Area, Row, Column)

' 创建扫码对象
create_data_code_2d_model ('QR Code', [], [], DataCodeHandle)

' 扫码
find_data_code_2d (Image1, SymbolXLDs, DataCodeHandle, 'stop_after_result_num', 'all', ResultHandles, DecodedDataStrings)
```


### 9点标定
``` VB
'标定, Row/Column 分别为图像中心坐标，Row1/Column1 为机械手坐标
area_center(SortedRegions, Area, Row, Column)
Row1 := [234, 23, ..., 234]
Column1 := [273, 234, ... , 290]
vector_to_hom_mat2d(Row, Column, Row1, Column1, HomMat2D)

'求解
affine_trans_point_2d(HomMat2D, Row2, Column2, Qx, Qy)
```