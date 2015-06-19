# 层次关系 

1. world 是根，所有的 Object 都在 world 中，每个 world 最终可以导出一个 obj 文件，所以会有 world 会有 save 和 load 方法

1. baseObject，抽象的方法有:
    - display() // 是不是可以考虑 display list

1. viewport <--> Viewer
