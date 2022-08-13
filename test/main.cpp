#include <iostream>
#include "../skiplist/skiplist.h"
using namespace std;

int main() {
    // 用于测试跳表类

    // 键值中的key用int型，如果用其他类型，需要自定义比较函数
    // 而且如果修改key的类型，同时需要修改skiplist.load_file函数
    skiplist<int, string> my_skiplist(6);
	my_skiplist.insert_element(1, "Nancy"); 
	my_skiplist.insert_element(3, "Taylor"); 
	my_skiplist.insert_element(7, "Josip"); 
	my_skiplist.insert_element(8, "Kae"); 
	my_skiplist.insert_element(9, "Ilu"); 
	my_skiplist.insert_element(19, "Dragan"); 
	my_skiplist.insert_element(19, "傻狍子"); 

    my_skiplist.size();

    my_skiplist.dump_file();

    my_skiplist.search_element(9);
    my_skiplist.search_element(18);


    my_skiplist.display_list();

    my_skiplist.delete_element(3);
    my_skiplist.delete_element(7);
    my_skiplist.delete_element(13);

    my_skiplist.size();

    my_skiplist.display_list();

    // 用于测试load_file函数
    skiplist<int, string> my_skiplist_backup(6);

    my_skiplist_backup.display_list();

    my_skiplist_backup.load_file();

    my_skiplist_backup.size();

    my_skiplist_backup.display_list();

    my_skiplist_backup.delete_element(9);

    my_skiplist_backup.insert_element(6, "Brande");

    my_skiplist_backup.insert_element(20, "Reyhan");

    my_skiplist_backup.search_element(20);

    my_skiplist_backup.size();

    my_skiplist_backup.display_list();
}
