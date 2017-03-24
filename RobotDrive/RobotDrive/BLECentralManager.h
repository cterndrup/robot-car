//
//  BLECentralManager.h
//  RobotDrive
//
//  Created by COLIN TERNDRUP on 3/13/17.
//  Copyright © 2017 COLIN TERNDRUP. All rights reserved.
//

#import <CoreBluetooth/CoreBluetooth.h>

@interface BLECentralManager : CBCentralManager <CBCentralManagerDelegate>

+ (BLECentralManager *)sharedBLECentralManager;

- (void) scanForPeripheralsWithOptions: (NSDictionary<NSString *,id> *) opts;

@end
