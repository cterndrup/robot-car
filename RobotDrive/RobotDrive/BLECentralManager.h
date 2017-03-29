//
//  BLECentralManager.h
//  RobotDrive
//
//  Created by COLIN TERNDRUP on 3/13/17.
//  Copyright © 2017 COLIN TERNDRUP. All rights reserved.
//

#import <CoreBluetooth/CoreBluetooth.h>

@protocol BLECentralManagerDiscoveryAlertDelegate

- (BOOL)bleCentralManager:(CBCentralManager *)central willConnectForPeripheral:(CBPeripheral *)peripheral;
- (void)bleCentralManager:(CBCentralManager *)central connectionToPeripheral:(CBPeripheral *)peripheral didTimeoutWithMessage:(NSString *)message;

@end

@interface BLECentralManager : CBCentralManager <CBCentralManagerDelegate>

@property (weak) id <BLECentralManagerDiscoveryAlertDelegate> alertDelegate;

+ (BLECentralManager *)sharedBLECentralManager;

- (id)alertDelegate;
- (void)setAlertDelegate:(id<BLECentralManagerDiscoveryAlertDelegate>)alertDelegate;
- (void)scanForPeripheralsWithOptions:(NSDictionary<NSString *,id> *)opts;

@end
