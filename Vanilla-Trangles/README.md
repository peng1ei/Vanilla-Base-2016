## 面剔除 (Face culling)

* [面剔除](https://learnopengl-cn.readthedocs.io/zh/latest/04%20Advanced%20OpenGL/04%20Face%20culling/) 

OpenGL允许检查所有正面朝向（Front facing）观察者的面，并渲染它们，而丢弃所有背面朝向（Back facing）的面，
这样就节约了我们很多片段着色器的命令（它们很昂贵！）。我们必须告诉OpenGL我们使用的哪个面是正面，哪个面是反面。
OpenGL使用一种聪明的手段解决这个问题——分析顶点数据的连接顺序（Winding order）。

每三个顶点都形成了一个包含着连接顺序的基本三角形。OpenGL使用这个信息在渲染你的基本图形的时候决定这个三角形是
三角形的正面还是三角形的背面。默认情况下，**逆时针**的顶点连接顺序被定义为三角形的**正面**。把所有三角的顶点
都定义为逆时针是一个很好的习惯。


* 顺时针（clockwise winding）
* 逆时针（counter-clockwise winding）

OpenGL默认关闭面剔除选项。所以如果我们需要面剔除功能的话，需要手动开启：

```c
glEnable(GL_CULL_FACE);
```

面剔除功能只对像立方体这样的封闭形状有效（可提高渲染效率）。如果某个物体它的前、后面都必须是可见的，则需要关闭
面提出功能。


OpenGL允许我们改变剔除面的类型。

```c
// GL_BACK：只剔除背面。(默认值)
// GL_FRONT：只剔除正面。
// GL_FRONT_AND_BACK：剔除背面和正面。
glCullFace(GL_BACK);
```

还可以告诉OpenGL使用顺时针而不是逆时针来表示正面，这通过glFrontFace来设置：

```c
// 默认值是GL_CCW，它代表逆时针，GL_CW 代表顺时针顺序。
glFrontFace(GL_CCW);
```

面剔除是OpenGL提高效率的一个强大工具，它使应用节省运算。**你必须跟踪下来哪个物体可以使用面剔除，哪些不能**。


