# BitMap 图像处理

<center>
    1900012476 夏罗生
</center>

## 使用方法

```powershell
process_bmp.exe input.bmp rotate angle out.bmp	// 旋转角度
process_bmp.exe input.bmp resize newWidth newHeight out.bmp // resize
process_bmp.exe input.bmp h_flip out.bmp	// 水平翻转
process_bmp.exe input.bmp v_flip out.bmp	// 垂直翻转
```

## BitMap 文件格式

### 文件头

位图格式的文件头长度可变，而且其中参数繁多。但是我们日常生活中遇到的 .bmp 格式图片的文件头长度绝大多数都是 54 字节，其中包括 14 字节的 Bitmap 文件头以及 40 字节的 DIB (Device Independent Bitmap) 数据头，或称位图信息数据头（BItmap Information Header）。

![preview](https://s2.loli.net/2022/04/29/sOhFxTJ4nfMoycW.png)

![preview](https://s2.loli.net/2022/04/29/RCKlqe9IhbUZPSx.jpg)

### 原始位图数据 Raw Bitmap Data

数据按照像素行进行包装，便于读取。但是这并不是全部，因为其中还可能会有补零（zero-padding）。这涉及到计算机的数据结构对齐（data structure alignment）的问题。

主流的 CPU 每次从内存中读取并处理数据块（chunk），且通常为 32 比特（4 字节）。因此，为了提升读取效率，位图每行的数据（字节）都需要是 4 的倍数。不可避免地，有些时候每行的结尾就会出现补零（其实补其他任意数字也是可以的，但常见都是补 0）。

每行补零的字节数的计算公式为：

```c++
(4 - ((biWidth * BYTE_PER_PIX) & 0x3)) & 0x3
```

`&` 符号表示 按位与 运算符，`&3` 表示对 4 取余。

## 图像旋转

### 坐标变换

规定顺时针旋转为正，x 轴向右，y 轴向上。

以图像中心（a,b）为旋转中心，旋转角度 $\theta$，计算图像上任一点（x1,y1）旋转之后的坐标（x2,y2）。

以（a,b）为新坐标原点，则（x1,y1）的新坐标为
$$
x_1'=x_1-a \\
y_1'=y1-b\\
$$
（x2,,y2）的新坐标为
$$
x_2'=cos\theta x_1'+sin\theta y_1' \\
y_2'=-sin\theta x_1'+cos\theta y_1'\\
$$
则（x2,y2）的原坐标为
$$
x_2=x_2'+a=cos\theta(x_1-a)+sin\theta(y_1-b)+a	\\
y_2=y_2'+b=-sin\theta(x_1-a)+cos\theta(y_1-b)+b
$$

### 双线性插值

如果旋转之后的像素点并不是很如人意的落在像素点上，而是落在临近的四个像素点构成的正方形区域内（而且这种情况应该是很常见的一种），我们通过双线性插值确定旋转之后的像素的颜色值。

![num2](https://s2.loli.net/2022/04/29/pOkXc8MQUHqtaBJ.png)

### 实现旋转

新图像的高度和宽度取决于两条对角线。只需要求出两条对角线旋转后的宽度和高度，两者的最大值就是新图像的宽度和高度。下面给出求一条对角线宽度和高度的方法。

![img](https://s2.loli.net/2022/04/29/17qIRAu4C6x5PlE.png)

然后对应新图层的每一个像素点，计算出对应的原始图像中的像素点，使用双线性插值确定颜色值。