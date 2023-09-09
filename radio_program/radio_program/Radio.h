class Radio
{
private:
    /* data */
public:
    Radio(/* args */);

    bool listen_for_signal();

    void send_data_to_flight_computer();

    void send_data_to_ground_station();

    bool recieve_canbus_data();

    void main();
};


