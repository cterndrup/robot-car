//
//  BLEPeripheral.h
//  RobotDrive
//
//  Created by COLIN TERNDRUP on 3/23/17.
//  Copyright © 2017 COLIN TERNDRUP. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@interface BLEPeripheral : NSObject <CBPeripheralDelegate>

+ (BLEPeripheral *)sharedBLEPeripheral;

- (void)setPeripheral:(CBPeripheral *) peripheral;
- (void)discoverServices;

@end
