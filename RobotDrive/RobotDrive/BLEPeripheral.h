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

@property CBService *bleBatteryService;
@property CBService *bleRobotDriveService;
@property NSArray<CBCharacteristic *> *bleBatteryCharacteristics;
@property NSArray<CBCharacteristic *> *bleRobotDriveCharacteristics;

+ (BLEPeripheral *)sharedBLEPeripheral;

- (void)setPeripheral:(CBPeripheral *)peripheral;
- (void)discoverServices;
- (BOOL)isConnected;
- (void)setRobotDriveSpeed:(NSData *)speed;
- (void)setRobotDriveDirection:(NSData *)direction;

@end
