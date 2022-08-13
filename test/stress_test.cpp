#include <iostream>
#include <chrono>
#include <cstdlib>
#include <pthread.h>
#include <time.h>
#include "../skiplist/skiplist.h"
using namespace std;

#define NUM_THREADS 1
#define TEST_COUNT 100000
skiplist<int, string> skipList(18);

void *insertElement(void* threadid) {
    long tid; 
    tid = (long)threadid;
    cout << tid << endl;  
    int tmp = TEST_COUNT/NUM_THREADS; 
	for (int i=tid*tmp, count=0; count<tmp; i++) {
        count++;
		skipList.insert_element(rand() % TEST_COUNT, "a"); 
	}
    pthread_exit(NULL);
}

void *getElement(void* threadid) {
    long tid; 
    tid = (long)threadid;
    cout << tid << endl;  
    int tmp = TEST_COUNT/NUM_THREADS; 
	for (int i=tid*tmp, count=0; count<tmp; i++) {
        count++;
		skipList.search_element(rand() % TEST_COUNT); 
	}
    pthread_exit(NULL);
}

int main() {
    srand (time(NULL));  
    {
        // 用于insert插入压力测试
        pthread_t threads[NUM_THREADS];
        int rc;
        int i;

        auto start = chrono::high_resolution_clock::now();

        // 其实我不是很懂为什么要设置另外一个线程进行插入/删除操作，直接在主线程中insert/search一样的啊，耗时倒是差不多
        // 是为了模拟客户端/服务端交互的过程吗？
        // for (i = 0; i < TEST_COUNT; ++i) {
        //     skipList.insert_element(rand() % TEST_COUNT, "a");
        // }

        for( i = 0; i < NUM_THREADS; i++ ) {
            cout << "main() : creating thread, " << i << endl;
            rc = pthread_create(&threads[i], NULL, insertElement, (void *)i);

            if (rc) {
                cout << "Error:unable to create thread," << rc << endl;
                exit(-1);
            }
        }

        void *ret;
        for( i = 0; i < NUM_THREADS; i++ ) {
            if (pthread_join(threads[i], &ret) !=0 )  {
                perror("pthread_create() error"); 
                exit(3);
            }
        }
        auto finish = chrono::high_resolution_clock::now(); 
        chrono::duration<double> elapsed = finish - start;
        cout << "insert elapsed:" << elapsed.count() << endl;

        skipList.dump_file();
    }

    // {
    //     // 用于search查询压力测试

    //     skipList.load_file();
    //     pthread_t threads[NUM_THREADS];
    //     int rc;
    //     int i;
    //     auto start = chrono::high_resolution_clock::now();

    //     // for (i = 0; i < TEST_COUNT; ++i) {
    //     //     skipList.search_element(rand() % TEST_COUNT);
    //     // }

    //     for( i = 0; i < NUM_THREADS; i++ ) {
    //         cout << "main() : creating thread, " << i << endl;
    //         rc = pthread_create(&threads[i], NULL, getElement, (void *)i);

    //         if (rc) {
    //             cout << "Error:unable to create thread," << rc << endl;
    //             exit(-1);
    //         }
    //     }

    //     void *ret;
    //     for( i = 0; i < NUM_THREADS; i++ ) {
    //         if (pthread_join(threads[i], &ret) !=0 )  {
    //             perror("pthread_create() error"); 
    //             exit(3);
    //         }
    //     }

    //     auto finish = chrono::high_resolution_clock::now(); 
    //     chrono::duration<double> elapsed = finish - start;
    //     cout << "get elapsed:" << elapsed.count() << endl;
    // }

	
    pthread_exit(NULL);
    return 0;

}
