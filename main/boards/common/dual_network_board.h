#ifndef DUAL_NETWORK_BOARD_H
#define DUAL_NETWORK_BOARD_H

#include "board.h"
#include "wifi_board.h"
    #include "ml307_board.h"
#include <memory>


// 双网络板卡类，可以在WiFi和ML307之间切换
class DualNetworkBoard : public Board {
private:
    // 使用基类指针存储当前活动的板卡
    std::unique_ptr<Board> current_board_;
    NetworkType network_type_ = NetworkType::ML307;  // Default to ML307

    // ML307的引脚配置
    gpio_num_t ml307_tx_pin_;
    gpio_num_t ml307_rx_pin_;
    gpio_num_t ml307_rst_pin_ = GPIO_NUM_NC;
    gpio_num_t ml307_pwr_pin_ = GPIO_NUM_NC;
    gpio_num_t ml307_dtr_pin_ = GPIO_NUM_NC;
    gpio_num_t ml307_wakeup_pin_ = GPIO_NUM_NC;
    size_t ml307_rx_buffer_size_;
    
    // 从Settings加载网络类型
    NetworkType LoadNetworkTypeFromSettings(int32_t default_net_type);
    
    // 保存网络类型到Settings
    void SaveNetworkTypeToSettings(NetworkType type);

    // 初始化当前网络类型对应的板卡
    void InitializeCurrentBoard();
 
public:
    //DualNetworkBoard(gpio_num_t ml307_tx_pin, gpio_num_t ml307_rx_pin, size_t ml307_rx_buffer_size = 4096, int32_t default_net_type = 1);
    DualNetworkBoard(gpio_num_t ml307_tx_pin, gpio_num_t ml307_rx_pin, gpio_num_t ml307_rst_pin, gpio_num_t ml307_pwr_pin, 
                     gpio_num_t ml307_dtr_pin, gpio_num_t ml307_wakeup_pin, size_t ml307_rx_buffer_size = 4096, int32_t default_net_type = 1);
    virtual ~DualNetworkBoard() = default;
 
    // 切换网络类型
    void SwitchNetworkType();
    
    // 获取当前网络类型
    NetworkType GetNetworkType() const override {
        return network_type_;
    }
    
    // 获取当前活动的板卡引用
    Board& GetCurrentBoard() const { return *current_board_; }
    
    // 重写Board接口
    virtual std::string GetBoardType() override;
    virtual void StartNetwork() override;
    virtual Http* CreateHttp() override;
    virtual WebSocket* CreateWebSocket() override;
    virtual Mqtt* CreateMqtt() override;
    virtual Udp* CreateUdp() override;
    virtual const char* GetNetworkStateIcon() override;
    virtual void SetPowerSaveMode(bool enabled) override;
    virtual std::string GetBoardJson() override;
    virtual std::string GetDeviceStatusJson() override;
};

#endif // DUAL_NETWORK_BOARD_H 