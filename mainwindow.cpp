#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    client_port_name("/jtc_tuner_gui/params:o"),
    robot_name("icub"),
    save_location("./")
{
    ui->setupUi(this);
    ui->robotName_input->setText(robot_name.c_str());

    rpc_client.open(client_port_name);

    part_name_vector.push_back("right_arm");
    part_name_vector.push_back("left_arm");
    part_name_vector.push_back("right_leg");
    part_name_vector.push_back("left_leg");
    part_name_vector.push_back("torso");

    setWindowIcon(QIcon(":/images/app_icon.png"));
    setWindowTitle("JTC Tuner");

    part_name = part_name_vector[0]; // Start with first part
    joint_index = 0; // all parts have at least 1 joint
    n_joints = 1;

    for(int i=0; i<part_name_vector.size(); ++i)
        ui->part_combo_box->addItem(part_name_vector[i].c_str());

    connectToPartJtcPort();
}

MainWindow::~MainWindow()
{
    rpc_client.close();
    delete ui;
}

void MainWindow::on_robotName_input_editingFinished()
{
    robot_name = ui->robotName_input->text().toStdString();
    connectToPartJtcPort();
}


bool MainWindow::connectToPartJtcPort()
{
    if(yarp.isConnected(client_port_name, server_port_name)) {
        yarp.disconnect(client_port_name, server_port_name);
    }
    server_port_name = "/" + robot_name + "/jtc/" + part_name + "/params:i";
    std::cout<< server_port_name << std::endl;
    bool ret = yarp.connect(client_port_name, server_port_name);
    ui->joint_combo_box->clear();
    getJointNames();
    return ret;
}

void MainWindow::getJointNames()
{
    yarp::os::Bottle request, reply;
    request.addString("get");
    request.addString("joint_list");
    rpc_client.write(request, reply);
    ui->joint_combo_box->clear();
    for(int i=0; i<reply.size(); ++i){
        ui->joint_combo_box->addItem(reply.get(i).asString().c_str());
    }
}



void MainWindow::on_joint_combo_box_activated(int index)
{
    joint_index = index;
    original_jtc = getJointParameters();
    jtc = original_jtc;
    populateJtcParameterInputFields();
}

void MainWindow::on_part_combo_box_activated(int index)
{
    saveJtcParameters();
    part_name = part_name_vector[index];
    if (!connectToPartJtcPort()) {
        std::cout << "Part not responding: " << part_name << std::endl;
    }
}


JtcParameters MainWindow::getJointParameters()
{
    JtcParameters ret;
    yarp::os::Bottle request, reply;
    request.addString("get");
    request.addString("params");
    request.addInt(joint_index);
    rpc_client.write(request, reply);
    ret.fromBottle(reply);
    return ret;
}

JtcParameters MainWindow::sendJointParameters()
{
    JtcParameters ret;
    yarp::os::Bottle request, reply;
    request.addString("set");
    request.addInt(joint_index);
    jtc.toBottle(request);
    rpc_client.write(request, reply);
    ret.fromBottle(reply);
    return ret;
}

void MainWindow::on_pushButton_clicked()
{
    jtc = original_jtc;
    populateJtcParameterInputFields();
}

void MainWindow::populateJtcParameterInputFields()
{
    ui->kp_input->setText(QString::number(jtc.kp));
    ui->kp_input->setText(QString::number(jtc.kp));
    ui->ki_input->setText(QString::number(jtc.ki));
    ui->kd_input->setText(QString::number(jtc.kd));
    ui->max_int_input->setText(QString::number(jtc.max_int));
    ui->max_pwm_input->setText(QString::number(jtc.max_pwm));
    ui->kv_input->setText(QString::number(jtc.kv));
    ui->kcp_input->setText(QString::number(jtc.kcp));
    ui->kcn_input->setText(QString::number(jtc.kcn));
    ui->coulombVelThr_input->setText(QString::number(jtc.coulombVelThr));
    ui->kff_input->setText(QString::number(jtc.kff));
    ui->frictionCompensation_input->setText(QString::number(jtc.frictionCompensation));
}

void MainWindow::on_joint_combo_box_currentIndexChanged(int index)
{
    joint_index = index;
    original_jtc = getJointParameters();
    jtc = original_jtc;
    populateJtcParameterInputFields();
}

void MainWindow::on_saveLocationButton_clicked()
{
//    QString filePath = QFileDialog::getOpenFileName();
    QString filePath = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    save_location = filePath.toStdString();
    QMessageBox::information(this, "New save location", save_location.c_str());
}

void MainWindow::saveJtcParameters()
{
    yarp::os::Bottle request, reply;
    request.addString("save");
    request.addString(save_location);
    rpc_client.write(request, reply);
    std::cout << reply.toString() << std::endl;
}

void MainWindow::on_kp_input_editingFinished()
{
    bool worked;
    double tmp = ui->kp_input->text().toDouble(&worked);
    if (worked){
        jtc.kp = tmp;
        jtc = sendJointParameters();
        populateJtcParameterInputFields();
    } else {
        std::cout << "That is an invalid input." << std::endl;
        ui->kp_input->setText(QString::number(jtc.kp));
    }
}

void MainWindow::on_ki_input_editingFinished()
{
    bool worked;
    double tmp = ui->ki_input->text().toDouble(&worked);
    if (worked){
        jtc.ki = tmp;
        jtc = sendJointParameters();
        populateJtcParameterInputFields();
    } else {
        std::cout << "That is an invalid input." << std::endl;
        ui->ki_input->setText(QString::number(jtc.ki));
    }
}

void MainWindow::on_kd_input_editingFinished()
{
    bool worked;
    double tmp = ui->kd_input->text().toDouble(&worked);
    if (worked){
        jtc.kd = tmp;
        jtc = sendJointParameters();
        populateJtcParameterInputFields();
    } else {
        std::cout << "That is an invalid input." << std::endl;
        ui->kd_input->setText(QString::number(jtc.kd));
    }
}

void MainWindow::on_max_int_input_editingFinished()
{
    bool worked;
    double tmp = ui->max_int_input->text().toDouble(&worked);
    if (worked){
        jtc.max_int = tmp;
        jtc = sendJointParameters();
        populateJtcParameterInputFields();
    } else {
        std::cout << "That is an invalid input." << std::endl;
        ui->max_int_input->setText(QString::number(jtc.max_int));
    }
}
void MainWindow::on_max_pwm_input_editingFinished()
{
    bool worked;
    double tmp = ui->max_pwm_input->text().toDouble(&worked);
    if (worked){
        jtc.max_pwm = tmp;
        jtc = sendJointParameters();
        populateJtcParameterInputFields();
    } else {
        std::cout << "That is an invalid input." << std::endl;
        ui->max_pwm_input->setText(QString::number(jtc.max_pwm));
    }
}
void MainWindow::on_kv_input_editingFinished()
{
    bool worked;
    double tmp = ui->kv_input->text().toDouble(&worked);
    if (worked){
        jtc.kv = tmp;
        jtc = sendJointParameters();
        populateJtcParameterInputFields();
    } else {
        std::cout << "That is an invalid input." << std::endl;
        ui->kv_input->setText(QString::number(jtc.kv));
    }
}
void MainWindow::on_kcp_input_editingFinished()
{
    bool worked;
    double tmp = ui->kcp_input->text().toDouble(&worked);
    if (worked){
        jtc.kcp = tmp;
        jtc = sendJointParameters();
        populateJtcParameterInputFields();
    } else {
        std::cout << "That is an invalid input." << std::endl;
        ui->kcp_input->setText(QString::number(jtc.kcp));
    }
}
void MainWindow::on_kcn_input_editingFinished()
{
    bool worked;
    double tmp = ui->kcn_input->text().toDouble(&worked);
    if (worked){
        jtc.kcn = tmp;
        jtc = sendJointParameters();
        populateJtcParameterInputFields();
    } else {
        std::cout << "That is an invalid input." << std::endl;
        ui->kcn_input->setText(QString::number(jtc.kcn));
    }
}
void MainWindow::on_coulombVelThr_input_editingFinished()
{
    bool worked;
    double tmp = ui->coulombVelThr_input->text().toDouble(&worked);
    if (worked){
        jtc.coulombVelThr = tmp;
        jtc = sendJointParameters();
        populateJtcParameterInputFields();
    } else {
        std::cout << "That is an invalid input." << std::endl;
        ui->coulombVelThr_input->setText(QString::number(jtc.coulombVelThr));
    }
}
void MainWindow::on_kff_input_editingFinished()
{
    bool worked;
    double tmp = ui->kff_input->text().toDouble(&worked);
    if (worked){
        jtc.kff = tmp;
        jtc = sendJointParameters();
        populateJtcParameterInputFields();
    } else {
        std::cout << "That is an invalid input." << std::endl;
        ui->kff_input->setText(QString::number(jtc.kff));
    }
}
void MainWindow::on_frictionCompensation_input_editingFinished()
{
    bool worked;
    double tmp = ui->frictionCompensation_input->text().toDouble(&worked);
    if (worked){
        jtc.frictionCompensation = tmp;
        jtc = sendJointParameters();
        populateJtcParameterInputFields();
    } else {
        std::cout << "That is an invalid input." << std::endl;
        ui->frictionCompensation_input->setText(QString::number(jtc.frictionCompensation));
    }
}

void MainWindow::on_saveButton_clicked()
{
    saveJtcParameters();
}
