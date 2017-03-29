//
//  DiscoverViewController.m
//  RobotDrive
//
//  Created by COLIN TERNDRUP on 2/23/17.
//  Copyright © 2017 COLIN TERNDRUP. All rights reserved.
//

#import "DiscoverViewController.h"

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
    
    // Set central manager's alert delegate
    [bleManager setAlertDelegate:self];
    
    // Scan for peripherals
    [bleManager scanForPeripheralsWithOptions: nil];
}

- (BOOL)bleCentralManager:(CBCentralManager *)central willConnectForPeripheral:(CBPeripheral *)peripheral {
    __block BOOL willConnect = false;
    
    NSString *connectionMsg = [NSString stringWithFormat:
                               @"Press Connect to connect to %@",
                               [peripheral name]];
    
    UIAlertController *connectionAlert =
        [UIAlertController alertControllerWithTitle:
         @"Peripheral discovered!" message:connectionMsg preferredStyle:
         UIAlertControllerStyleAlert];
    
    UIAlertAction *connect = [UIAlertAction actionWithTitle:@"Connect" style:
                              UIAlertActionStyleDefault handler:
                              ^(UIAlertAction *action){ willConnect = true; }];
    
    UIAlertAction *cancel = [UIAlertAction actionWithTitle:@"Cancel" style:
                             UIAlertActionStyleCancel handler:
                             ^(UIAlertAction *action){ willConnect = false; }];
    
    [connectionAlert addAction:connect];
    [connectionAlert addAction:cancel];
    [connectionAlert setPreferredAction:connect];
    [self presentViewController:connectionAlert animated:YES completion:nil];
    
    return willConnect;
}

- (void)bleCentralManager:(CBCentralManager *)central connectionToPeripheral:(CBPeripheral *)peripheral didTimeoutWithMessage:(NSString *)message {
    
    UIAlertController *connectionTimeoutAlert =
        [UIAlertController alertControllerWithTitle:
         @"Connection Timeout" message:message preferredStyle:
         UIAlertControllerStyleAlert];
    
    UIAlertAction *ok = [UIAlertAction actionWithTitle:@"OK" style:
                         UIAlertActionStyleDefault handler:
                         ^(UIAlertAction *action){
                             [central cancelPeripheralConnection:peripheral];
                         }];
    
    [connectionTimeoutAlert addAction:ok];
    [connectionTimeoutAlert setPreferredAction:ok];
    [self presentViewController:connectionTimeoutAlert animated:YES completion:nil];
}

@end
