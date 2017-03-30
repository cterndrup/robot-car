//
//  DriveViewController.m
//  RobotDrive
//
//  Created by COLIN TERNDRUP on 2/23/17.
//  Copyright © 2017 COLIN TERNDRUP. All rights reserved.
//

#import "DriveViewController.h"
#import "BLEPeripheral.h"

@interface DriveViewController ()

@end

@implementation DriveViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)robotSpeedDidChangeFromSender:(UISlider *)sender {
    float speed = [sender value];
    
    BLEPeripheral *robot = [BLEPeripheral sharedBLEPeripheral];
    [robot setRobotDriveSpeed:[NSData dataWithBytes:&speed length:
                               sizeof(float)]];
}

@end
