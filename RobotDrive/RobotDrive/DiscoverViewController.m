//
//  DiscoverViewController.m
//  RobotDrive
//
//  Created by COLIN TERNDRUP on 2/23/17.
//  Copyright © 2017 COLIN TERNDRUP. All rights reserved.
//

#import "DiscoverViewController.h"
#import "BLECentralManager.h"

@interface DiscoverViewController ()

@end

@implementation DiscoverViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)discoverClicked:(UIButton*)sender {
    // Retrieve the BLE Central Manager and begin discovery...
    BLECentralManager *bleManager = [BLECentralManager sharedBLECentralManager];
    
    [bleManager scanForPeripheralsWithOptions: nil];
}

@end
