class Recovery
{
private:
    /* data */
    bool chute_is_deployed = false;
public:
    Recovery(/* args */);

    void send_chute_signal();

    void retrieve_data();

    bool calculate_apoge();

    bool check_for_flight_computer_signal();

    void main();
};



