## 06 数据结构基础


推荐：

* UVA-422 	栈经典习题
* UVA-12677 双向链表好题
* UVA-122 	蛮好的一个题，可以用建树来做，也可以用字符串来做。
* UVA-548 	经典二叉树习题
* UVA-1103 	当年WF的签到题，观察力+DFS，很有意思的一道题。
* UVA-816 	BFS套路题，有一些细节处理，对于新人比较锻炼代码能力。
* UVA-1572  DFS找环的经典题，考察基本算法和构图能力。
* UVA-1599  经典的两次BFS题目
* UVA-506   Linux包依赖背景的题目，查找和简单递归
* UVA-1600  优先队列BFS
* UVA-12166 需要先数学证明一下，处理的时候递归就行了。
* UVA-806	还不错的递归模拟题，有实际工程背景。
* UVA-10410 考察树的bfs和dfs序的特点 
* UVA-810 	BFS裸题，考察路径输出和状态转移。

不推荐：

* UVA-10562 输入数据说明错误，表示不明，故意挖坑。

---

### UVA-514 Rails

题意： 判断是否是出栈序列。

思路： 

1. 出栈序列中，比$a_i$小的后面数必然是降序的。所以枚举一下就可以了。 $O(n^3)$ [code](./uva514.cpp)
2. 模拟栈操作。序列中的a_i,如果它是已出的最大的数，那么把比它小还没有入栈的数入栈；否则如果它等于栈顶，出栈；否则不是出栈序列。 $(O(n))$ [code](./uva514-1.cpp)


### UVA-442 Matrix Chain Multiplication

题意：计算矩阵乘法的计算次数

思路：栈模拟，由于输入表达式都是合法的，所以遇到右括号就弹栈两次，计算代价，再压栈新矩阵的行列即可。 [code](./uva442.cpp)

### UVA-11988 Broken Keyboard

题意：一个输入字符串，`[`表示按`home`键，从行头开始输入，,`]`表示按`end`键，从行尾开始输入，求输出字符串。

思路： 链表。[code](./uva11988.cpp)

### UVA-12657 Boxes in a Line

题意: 一排n个数，四种指令，`1 x y` 将x放在y左边;`2 x y` 将x放在y右边; `3 x y` 交换x,y; `4` 逆序。m次指令后，奇数位的累加和。

思路：手写一个双向链表，前面3种操作对应操作每个节点的prev和next即可，操作4只要把方向变量取反即可。注意`3 x y`中x和y相邻的特殊情况。 [code](./uva12657.cpp)

### UVA-679 Dropping Balls

题意： 一个满二叉树，编号从$1$到$2^D - 1$。非叶子节点有一个开关，初始为开，每过一次球，状态翻转。球每次都从根开始下落，问第I个球落在哪个叶子节点上。保证I不会超过叶子节点数量。

思路： 找规律，把D=4的情况列出来，发现结果等于 1 << (D-1) | (I-1)的2进制逆序。 [code](./uva679.cpp)


### UVA-122 Trees on the level

题意： 给一个二叉树的节点编号，以及从根到这个节点的路径，问树按层次遍历的结果。不构成树，输出"not complete"。

思路：看上去需要重构这个二叉树，然后遍历，其实不用。
直接判断是否满足以下条件即可。

1. 根节点是否唯一。
2. 节点路径是否唯一。
3. 节点路径的前缀(前n-1个)路径节点有且仅有一个。

用multimap存<路径，编号>,然后枚举即可。注意自定义比较函数。

看题目的comment说标程有问题，没有考虑多个根不合法的情况。

[code](./uva122.cpp)


### UVA-548 Tree

题意：给一个二叉树的中序和后序遍历，求这个树从根到哪个叶子节点的路径点权和最小，如果存在多个满足条件的叶子，输出点权最小的叶子。

思路：二叉树的中序与后序可以唯一确定一个二叉树，用分治重构二叉树即可。
可以在重构的过程中维护节点的leaf，sum，分别表示从这个点为根的最短路径的叶子和路径权值。当然，也可以重构之后写个dfs来找。我用的是前面的方法。[code](./uva548.cpp)

### UVA-839 Not so Mobile

题意: 一个树状天平，问是否平衡？

思路：递归即可。 [code](./uva839.cpp)

### UVA-699 The Falling Leaves

题意：一个二叉树，每个节点有个x坐标，左孩子在其x-1位置，右孩子在其x+1位置，求所有坐标上节点的累加和。

思路：递归，把对应位置上的节点加到数组上即可。[code](./uva699.cpp)

### UVA-297 Quadtrees 

题意： 一个四分树表示$32 \times 32$的二值图，`f`表示当前层全黑，`e`表示当前层全白，`p`表示当前层杂色。给两个四分树的前序遍历，求合并以后，图像中黑点的数量。

思路：递归把二值图画出来，由于只有合并操作，所以在同一幅上面画两次就可以了，用了位压缩。[code](./uva297.cpp)

### UVA-572 Oil Deposits 

题意：`@`表示油库，8个方向相连，相连的属于同一个油库。问有几个不同的油库？

思路：dfs求联通分量。 [code](./uva572.cpp)

### UVA-1103 Ancient Messages

题意：给一个二进制表示的二值图像，识别其中的象形文字。不同象形文字中间的洞数量不一样。

思路：

1. 把图像扩两圈，0圈为背景色`2`，1圈为`0`,2圈开始为图像；
2. 先把外面的`0`染成背景色`2`；
3. 枚举所有点，如果是`1`,做dfs，如果发现`0`,洞数量+1,把其连通的`0`全部染成`2`。

[code](./uva1103.cpp)

### UVA-816 Abbott's Revenge

题意： 最多$9 \times 9$个网状节点，节点按进入的方向能去向不同的相邻的节点。问从起点到终点的最短路径。

思路：

1. 处理地图，把每个节点的四个方向设置允许的去向(根据进入方向`NESW`和`FLR`转换过来)。
2. 标准BFS，注意记录路径。这里最好用手写的队列，这样只需要记录前继节点即可；如果使用`queue`容器，需要在节点里记录到达路径。
3. 输出路径。由于记录的是前继节点，用递归或者栈来打印路径。 

[code](./uva816.cpp)

### UVA-10129 Play on Words

题意: 若干单词，问是否能组成一条接龙(前面单词的最后一个字符是后面单词的第一个字符)链。

思路: 判断一个有向图是否存在欧拉路。欧拉路判定：所有点入度和出度不超过1，为1的入度和出度点最多有1个。另外，需要判弱连通性，直接dfs或者并查集都可以。

[code](./uva10129.cpp)


### UVA-10562 Undraw the Trees

题意： 一个树的字符图，求输出树对应的字符串。

思路：递归套路题，主要是题目坑。 

1. 可能树图为空，直接给一个`#`的输入结束
2. 横线长度比下面子树节点的长度长，而子树节点最后是个串结束符。 

[code](./uva10562.cpp)



### UVA-1572 Self-Assembly 

题意： n种分子，每个分子上有四个接口，接口用两个字符表示，大写字母和加减号（00无视）。
接口如果同字符的加减，可以连接。问是否可以组成无限长的链接？

思路： 明显是一个找环的题。算法明确了，后面就是建图了。

一开始思路有点乱，以为是无向图，发现不对，比如分子1有1个A+，分子2有1个A-，这两个只能连接一次，不能再连接了。改成有向图，把一个分子构造成最多四个点， 每个点一个入口，其他为出口，结果超时了[tle](./uva1572_tle.cpp)。稍微有点疑惑，因为题目说的分子数最多为4万，点数不会超过16万，不应该超时才是，估计是堆了很多组样例吧。再仔细想想，构图使用接口作为点，则点数不会超过52个，然后就过了。[ac](./uva1572.cpp)

dfs 有向图找环算法： 标记访问状态为未访问，正在访问，结束访问三种。如果一个节点处于正在访问状态，又将被重复访问，则必然在dfs生成树上存在回边，存在环。


### UVA-1599 Ideal Path

题意：
n点无向图，边权为1，边上还有颜色，求1到n的最短路的颜色序列的最小字典序。

思路：

先从n开始，bfs，染色，得到最短路生成树，并标明层次；
再从1开始，把最短路生成树按层次遍历，每一层取个最小颜色。

[code](./uva1599.cpp)

书上说有一种只做一次的搞法，想了很久，不知道怎么搞。

### UVA-506 System Dependencies

题意：

Linux系统的包依赖，安装，删除。
安装分两种，一种是因为依赖关系被隐式安装的，一种是显式安装（install命令安装）的。

注意的几个点：
1. 删除时候的显示顺序是先显示根项，再显示子项；
2. 删除时，只有隐式安装的且没有被依赖包会被删除。
3. List命令时，是按安装顺序输出
4. 题目中没有说如果某包被安装了，然后又加依赖会怎么样。从AC的情况来看，没有这种情况。

思路：

1. 包的状态包括未安装，隐式安装，显式安装。
2. 当安装或者删除某包时，维护这个包所有依赖包的被引用次数。
3. 全局ID为安装的流水号，维护map，为已安装包的流水号和名字。

[code](./uva506.cpp)



### UVA-673 Parentheses Balance

题意：

问一个只含圆括号和方括号的字符串是否是括号匹配的。

思路：
经典的栈题目，左括号进栈，右括号看是否匹配和弹栈。
最后栈空为匹配。注意输入可能为空字符串。

[code](./uva673.cpp)

### UVA-712 S-Trees 

题意：

将一个布尔表达式表示为一个完全二叉树，完全二叉树，一共n+1层，将布尔向量的分量赋值到某一层的所有节点。
已知所有布尔运算的最后的值（完全二叉树的叶子节点），现在询问m次，每次给一个布尔向量，询问此布尔向量的布尔表达式的值。

思路：

用数组存储完全二叉树的叶子节点，利用二叉堆的下标性质来定位坐标即可。 [code](./uva712.cpp)


### UVA-536 Tree Recovery

题意：

已知二叉树的前序和中序遍历，求后序遍历。

思路：

数据结构教科书后习题，利用前序遍历的第一个节点是根节点，其在中序遍历中前面是左子树，后面是右子树。递归建树，再后序遍历即可。 [code](./uva536.cpp)

### UVA-439 Knight Moves

题意：
国际象棋，马从起点到终点的步数。

思路：
裸bfs。 [code](./uva439.cpp)

### UVA-1600 Patrol Robot

题意：

一个网格地图，允许最多连续k次通过障碍点的情况下，从（1,1）到（n,m）的最短距离。

思路：

优先队列BFS，记录每个点已经连续第t次通过的步数。 [code](./uva1600.cpp)

### UVA-12166 Equilibrium Mobile

题意：

二叉树左右子树节点权和都相等时，需要调整节点权值的最少数量。

思路：

先证明一下结果是叶子节点数减去加权节点权值（节点权值* (1 << depth））出现最多的次数。
考虑节点对于根的贡献，这个节点如果不修改，那么对于根来说，其值为 节点权值 * (1 << depth）。
所以，结论成立。

1. 用栈记录所有左括号对应的右括号的位置。
2. 手写一个解析表达式，递归即可。[code](./uva12166.cpp)

* 题目没说字符串长度，第一次RE了，后我开到2M。


### UVA-804 Petri Net Simulation

题意：

Petri网络，NP个点，NT个事务，事务的输入端连接的点有足够的token时激发，将所有输入的token转到输出端,输出端到对应的点。
问你在给定轮次下，网络是否是活的（所有事务无法激发认为网络死亡）。

思路：

阅读、模拟题。挺无聊的，而且题目是有歧义的，比如同时多个事务可激发时，优先顺序的问题，不过好像数据里并没有这种情况。[code](./uva804.cpp)


### UVA-806 Spatial Structures

题意：

一个n * n的二值图像做四叉树编码和译码，n为2的幂次。
四叉树节点从叶子到根，按5进制进行编码（从上到下，从左到右依次为1到4）。

输出节点值时，每行最多输出12个。
样例之间有空行。

思路：

递归模拟就可以了。
编码：当整个区块图像都是1时，插入编码值；否则，枚举四个分区块，递归编码。
译码：当码值k是0时，设置对应区块为1；否则计算k%5代表的区块，递归即可。

[code](./uva806.cpp)

### UVA-127 "Accordian" Patience 

题意：

52张扑克，两个字符表示一张牌，排成一列，每次都从左到右，
如果某张牌左边第三张和它匹配（花色或者点数相同），将这张牌移到左边第三张上面；
否则如果和左边第一张匹配，将这张牌移到左边第一张上面；
问最后会变成几垛，每垛牌的数量。

思路：
模拟就可以了，一个list，每个元素是一个栈。[code](./uva127.cpp)

### UVA-246 10-20-30 

题意：

52张扑克（JQK为10点，A为1点，其他为数字点数），从左到右7个牌堆和一个deck。
一开始牌堆为空，所有的牌都在deck上。然后从左到右循环发牌。
如果某个牌堆上的牌满足以下三条（按顺序判断）的和为10,20,30中的一个。

 1. 头1张和最后1张。
 2. 头2张和最后2张。
 3. 最后3张

那么把这三张牌拿出来，按顺序放到deck的最后面。

并不断重复这个过程，直到牌堆没有满足条件的牌。
如果牌堆最后被清空，那么这个牌堆就会消失。

如果能清空所有的牌堆，那么就获胜。如果没有牌继续，那么失败。如果出现循环，那么是平局。
另外还需要输出之前一共发了多少次牌。

思路：

就是模拟。 <code> std::list<std::<list> > </code> 表示牌堆和deck，使用最后一个作为deck。
再用set来判重。

有个小疑问，感觉 除了记录牌堆的状态之外，应该再加上当前发牌的位置，才能判重，但是好像只记录牌堆状态就可以了，不知道怎么证明。

[code](./uva246.cpp)

### UVA-10410 Tree Reconstruction 

题意：

给一个树的bfs和dfs序（同级别按节点序号访问），要求每个节点的子节点。

思路:

在dfs序上，本节点v，和上一个节点u，只能是 

    1. u是v的兄弟， 当 bfs[v] = bfs[u] + 1;
    2. u是v的父亲， 当 bfs[v] > bfs[u] + 1;
    3. u是v的侄子， 这时，不断查找u的父亲，直到u满足条件1或者2。

[code](./uva10410.cpp)

### UVA-810 A Dicey Problem

题意：

一个迷宫，格子上有点数；一个6面骰子，问是否能从起点出发回到起点。
移动要求是相邻格子的点数为-1，或者骰子顶面的点数相同。骰子是翻滚移动的。

思路:
	显然，裸BFS。

	1. 骰子是固定的，所以顶面和正面就确定了这个骰子，构造一个矩阵，对应每个顶面的四个侧面。
		a. 左右翻滚时，正面不变，新顶面变成正面的右边或者左边。
		b. 上翻滚时，新顶面为旧正面，新正面为7 - 旧顶面
		c. 下翻滚时，新顶面为7 - 旧正面，新正面为旧顶面 

	2. 需要记录<x,y,top,face>四元组来判重

	3. 因为需要打印路径，最好手写队列，利用节点的前继来记录路径。

输出格式有点恶心，题目基本上就是个体力活。 [code](./uva810.cpp)


### UVA-215 Spreadsheet Calculator

题意:

一个电子表格，单元格表达式 = 数字 | 引用 | 表达式+表达式 | 表达式-表达式。
告诉你电子表格所有单元格的表达式，求表格单元格的值。
如果存在循环引用，输出存在循环的单元格，否则输出整个电子表格。

思路：

    明显一个表达式解析和dfs的题。

    1. 解析表达式，记录单元格的值，依赖的引用。解析过程中，如果是数字，就直接加到单元格的值中，如果是引用就记录下来。
    2. 对于每个格子，dfs其依赖的单元格的值，并将值加到单元格的值中。
    3. 根据dfs中是否存在环，输出对应的结果。

    注意的是，数字可能是负数的。

[code](./uva215.cpp)

### UVA-12118 Inspector's Dilemma 

题意：

V个城市，双向路连接，必须要经过若干个城市之间的E条道路，从任意起点出发到任意终点结束，每条路代价都为T，问最少代价。

思路：

欧拉路判定和联通块数量。

不用管孤立点，然后dfs求联通块数量m和每个块内奇点的数量。 
如果某块中的奇点数大于2，那么每多2个点，就要多走1条边。
再加上需要多走m-1条边。

[code](./uva12118.cpp)

