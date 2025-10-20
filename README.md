# pcap01
电容测量芯片PCap01驱动，基于STM32F103C8T6芯片，HAL库实现。
# 文件说明
**pcap01.c**:添加示例寄存器配置及标准固件，封装常用接口，如发送8，24，32位读写命令；写reg0~reg10，写sram等。
**pcap01.h**:包含命令值宏定义，pcap01句柄等。
**pcap01_interface.c**:接口层，使用SPI实现，示例中使用HAL库，用户可更换其他。主要包括SPI片选使能，读写接口。
**pcap01_interface.c**:接口层头文件声明。
**pcap01_basic.c**:使用示例，如创建句柄，链接函数，初始化配置，读取差分测量的电容数据等。
**pcap01_basic.h**:对应头文件。
# 移植说明
1. 添加pcap01.c和pcap01.h，添加头文件路径和源文件。
2. 参考pcap01_interface.*，实现4个函数接口，已使用HAL库示例。
3. 参考pcap01_basic.*，实现初始化，配置寄存器，写入sram，读取测量结果等函数，示例已实现，根据需要修改。
4. 添加所有修改后文件及路径，编译调试。
5. 主函数或任务中添加·pcap_basic_init(&pcap);·，
···
float capacity1, capacity2, capacity3;
if (pcap_basic_read_diff(&pcap, 0x1, &capacity1) == 0)
{
    printf("{C1}%5.3f\r\n", capacity1);
}
if (pcap_basic_read_diff(&pcap, 0x2, &capacity2) == 0)
{
    printf("C2= %5.3f pF\r\n", capacity2);
}
if (pcap_basic_read_diff(&pcap, 0x3, &capacity3) == 0)
{
    printf("C3= %5.3f pF\r\n", capacity3);
}
···
