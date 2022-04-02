TEMPLATE = subdirs\

SUBDIRS += \
    VideoPlayer


#release编译之前：
#1.MusicPlayShow.cpp文件中，修改picture路径；
#2.ExitDialog.cpp文件中，修改退出窗口配置文件路径；

#问题
#01.模型数据为空，产生的错误，使用模型之前先判断数据源是否为空；
#02.随着侧边栏的改变，标题栏的内容作相应的改动；
#03.浏览器应该一个连接加载一个新页面的；
#04.搜索栏根据不同的页面展示下拉框。
