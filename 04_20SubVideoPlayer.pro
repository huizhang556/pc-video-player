TEMPLATE = subdirs\

SUBDIRS += \
    VideoPlayer


#2022-02-07  allcount = 11424 rows
#2022-05-27  allcount = 14616 rows

#release编译之前（已使用模式选择(release|debug)解决）：


#问题
#01.模型数据为空，产生的错误，使用模型之前先判断数据源是否为空；
