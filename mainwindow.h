#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QIcon>
#include <jtcparameters.h>

#include <iostream>

#include <yarp/os/Bottle.h>
#include <yarp/os/RpcClient.h>
#include <yarp/os/Network.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_robotName_input_editingFinished();

    void on_joint_combo_box_activated(int index);

    void on_part_combo_box_activated(int index);

    void on_pushButton_clicked();

    void on_joint_combo_box_currentIndexChanged(int index);

    void on_saveLocationButton_clicked();

    void on_kp_input_editingFinished();
    void on_ki_input_editingFinished();
    void on_kd_input_editingFinished();
    void on_max_int_input_editingFinished();
    void on_max_pwm_input_editingFinished();
    void on_kv_input_editingFinished();
    void on_kcp_input_editingFinished();
    void on_kcn_input_editingFinished();
    void on_coulombVelThr_input_editingFinished();
    void on_kff_input_editingFinished();
    void on_frictionCompensation_input_editingFinished();

    void on_saveButton_clicked();

private:
    bool connectToPartJtcPort();

    void getJointNames();

    JtcParameters getJointParameters();

    JtcParameters sendJointParameters();

    void populateJtcParameterInputFields();

    void saveJtcParameters();

private:
    Ui::MainWindow *ui;

    // Rpc Client
    yarp::os::Network yarp;
    yarp::os::RpcClient rpc_client;

    // Port info
    std::string robot_name;
    std::string part_name;
    std::string server_port_name;
    std::string client_port_name;

    // Current joint parameters
    int joint_index;
    int n_joints;

    JtcParameters jtc, original_jtc;

    std::vector<std::string> part_name_vector;

    std::string save_location;

};

#endif // MAINWINDOW_H
