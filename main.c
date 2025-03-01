#include "Vexample.h"
#include "verilated.h"
#include "verilated_vcd_c.h"  // 添加波形支持的头文件
#include <iostream>

int main() {
    // 启用波形跟踪
    Verilated::traceEverOn(true);
    Vexample* mux = new Vexample;
    VerilatedVcdC* tfp = new VerilatedVcdC;

    // 设置波形文件
    mux->trace(tfp, 99);  // 跟踪 99 层层次结构
    tfp->open("wave.vcd");

    // 初始化输入信号
    mux->a = 0;
    mux->b = 0;
    mux->sel = 0;

    // 遍历所有输入组合
    for (int sel = 0; sel < 2; sel++) {
        for (int a = 0; a < 2; a++) {
            for (int b = 0; b < 2; b++) {
                mux->a = a;
                mux->b = b;
                mux->sel = sel;
                mux->eval();  // 评估模块
                tfp->dump(10 * (sel * 4 + a * 2 + b));  // 记录波形
                std::cout << "sel=" << sel << " a=" << a << " b=" << b << " => y=" << (int)mux->y << std::endl;
            }
        }
    }

    // 清理
    delete mux;
    tfp->close();
    return 0;
}
