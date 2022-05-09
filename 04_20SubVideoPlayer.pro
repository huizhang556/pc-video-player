TEMPLATE = subdirs\

SUBDIRS += \
    VideoPlayer


#2022-02-07  allcount = 11424 rows

#release编译之前（已使用模式选择(release|debug)解决）：
#1.MusicPlayShow.cpp文件中，修改picture路径；
#2.ExitDialog.cpp文件中，修改退出窗口配置文件路径；
#3.PictureWidget.cpp文件中，修改轮播图的路径；
#4.GalleryItemForm.cpp文件中，55行修改图片路径；
#5.StackItemForm.cpp文件中，31行修改图片路径；

#问题
#01.模型数据为空，产生的错误，使用模型之前先判断数据源是否为空；
#02.随着侧边栏的改变，标题栏的内容作相应的改动；
#03.浏览器应该一个连接加载一个新页面的；
#04.搜索栏根据不同的页面展示下拉框。
