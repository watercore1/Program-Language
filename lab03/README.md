# 爬楼梯

<center>
    1900012476 夏罗生
</center>

## 斐波那契数列(Fibonacci sequence)

设 $F(n)$ 为爬 n 阶楼梯的可能的方法，那么最后一步可能是跨一级或者是跨两级，则递推式为 $F(n)=F(n-1)+F(n-2)$。

初始情况为 $F(1)=1,F(2)=2$，相当于从第三项开始的斐波那契数列，则把问题转化为了如何求解斐波那契数列。

## 递归方法

由于存在递推关系，所以很容易想到使用递归方法求解，时间复杂度为 $O(2^n)$，空间复杂度为 $O(1)$。

递归方法做了很多重复性的计算，中间项 $F(i)$ 计算了很多次，使用记忆化缓存进行优化。时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

由于要多次计算，所以在每次计算时，找到输入的最大项数，如果大于当前的记忆化数组，则扩充记忆化数组，否则直接输出记忆化数组中的对应项。

## 快速矩阵幂算法

构建矩阵形式的递推关系：
$$
\left[\begin{array}{}
1 & 1 \\
1 & 0
\end{array}\right]
\left[\begin{array}{}
F(n) \\
F(n-1)
\end{array}\right]
=
\left[\begin{array}{}
F(n+1) \\
F(n)
\end{array}\right]
$$
因此：
$$
\left[\begin{array}{}
F(n+1) \\
F(n)
\end{array}\right]
=
\left[\begin{array}{}
1 & 1 \\
1 & 0
\end{array}\right]^n
\left[\begin{array}{}
F(1) \\
F(0)
\end{array}\right]
$$
令：
$$
M=\left[\begin{array}{}
1 & 1 \\
1 & 0
\end{array}\right]
$$
因此只要我们能快速计算矩阵 $M$ 的 $n$ 次幂，就可以得到 $F(n)$ 的值。如果直接求取 $M^n$，时间复杂度是 $O(n)$。

可以使用分治算法加快幂运算，时间复杂度降为 $O(\log n)$。
