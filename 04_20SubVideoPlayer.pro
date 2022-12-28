TEMPLATE = subdirs\

#子目录默认运行第一个项目，选择性运行某一个项目，右键该项目-->运行
SUBDIRS += \
    VideoPlayer    #主程序
#    CreateCenter    #创作中心


#2022-02-07  allcount = 11424 rows
#2022-05-27  allcount = 14616 rows
#2022-09-04  allcount = 20304 rows
#2022-11-15  allcount = 37305 rows
#2022-12-18  allcount = 39305 rows

#问题
#01.模型数据为空，产生的错误，使用模型之前先判断数据源是否为空；
#02.使用管理员权限需要开启权限。
