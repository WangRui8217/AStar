# 1. AStar题目

已知如下图地图，黑色表示障碍物无法通行，要求实现避障算法寻找从红色起点出发到达绿色终点的最优路径。

![image](https://github.com/CallOfDuty8217/AStar/blob/main/images/1.png)

图1题目

要求：

（1）对图中的地图进行建模，抽象成类，对数据进行封装；

（2）思考寻路算法的实现，对问题进行拆解，对算法实现也要求抽象接口类；

（3）使用给定的C++工程模板，按照模板编写CMakeLists.txt，以及GoogleTest单元测试，DoxyGen注释的使用。

工程模板如下：

**https://github.com/filipdutescu/modern-cpp-template.git**

# 2.算法原理

A*算法运行主要分为搜索、估算代价、再搜索三个步骤[12]。

A算法在运行前构建Open_set（用于存储待处理的网格）和Close_set（用于存储不再进行处理的网格）两个列表，其实现了对路径搜索过程中基于A*算法数据结构的数据存储、计算与判断。网格的状态仅可设置为允许通过或不允许通过两种状态，例如：存在障碍区的网格或处于边界的网格设置为不允许通过状态。首先，在搜索阶段，先将起始点所在网格A计入Open_set，然后从A开始，检测其相邻的网格区域，采用八邻域搜索：搜索分为上下、左右、左上、左下、右上、右下八个方向，若被检测到的网格状态为允许通过，则将该网格加入Open_set，否则跳过该网格并继续检测，直至检测完成所有的领域网格，然后将A设置为这些网格的父节点，其邻域网格为子节点。这样设置的目的在于进行后续路径追踪回溯，最后将A从Open_set移出，并计入Close_set中。

![image](https://github.com/CallOfDuty8217/AStar/blob/main/images/2.png)

图2 八邻域搜索

然后，成本计算阶段，引入了启发式代价函数：F=G+H。

其中，F为总代价之和，G为从起点到当前点的准确计算代价，H为当前点移动到终止点的估算代价。通常采用的有曼哈顿距离、欧几里得距离和对角线距离作为距离代价函数评估。AStar算法的优劣主要体现在了启发函数的选取上，也是体现A*算法启发式计算的核心技术部分。

最后是再搜索阶段，基于之前已完成的步骤，从Open_set中选择F值最小的网格，设为V_0，针对被选择的网格V_0，首先将V_0移出Open_set，加入Close_set，然后检测所有与V_0相邻的网格，跳过其中在Close_set中或状态为不允许通过的网格，若网格不在Open_set中，则将其加入Open_set；若网格已经在Open_set中，则检查这条路径是否更优，即检查由V_0达到其相邻网格V_1是否具有更小的G值。若否，则不做任何操作；若具有更小的G值，则将V_1的父节点设置为V_0，然后更新V_1的F值与G值。

最后重复上述过程，直到终止点B加入到Open_set，得证路径已找到，根据网格之间的父子节点关系，回溯终点到起点A。

若Open_set为空后，终止点依旧未加入Open_set，说明路径未找到。

# 3. 算法流程

![image](https://github.com/CallOfDuty8217/AStar/blob/main/images/3.png)

图3 算法流程图

# 4. 算法实现

- struct PointInfo：
  - 结点坐标x、y；
  - 结点代价F、G、H(G表示从起点到当前点的精确代价，H表示从当前点到终点的预估代价，F=G+H)；
  - 前节点的指针pre；
  - 该结构体的初始化函数。
- class Astar：
  - get_G、get_H、get_F：计算结点代价F、G、H值；
  - 初始化数组map；
  - 初始化列表Open_set；
  - 初始化列表Close_set；
  - FindPath：用于寻找起点到终点的路径；
  - AvailPointsAround：遍历周围可达结点；
  - isAvail：判断周围结点是否可达；
  - isInSet：判断结点是否在列表中；
  - MinCostPoint：寻找并返回代价最小的点；
  - get_map：获取map；
  - getPath：将结点放入路径Path。
