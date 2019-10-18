## 06 数据结构基础


推荐：

* UVA-122 蛮好的一个题，可以用建树来做，也可以用字符串来做。

不推荐：


---

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