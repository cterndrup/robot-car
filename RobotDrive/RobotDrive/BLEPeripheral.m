//
//  BLEPeripheral.m
//  RobotDrive
//
//  Created by COLIN TERNDRUP on 3/23/17.
//  Copyright © 2017 COLIN TERNDRUP. All rights reserved.
//

#import "BLEPeripheral.h"

@interface BLEPeripheral ()

@property CBPeripheral *blePeripheral;

@property (readonly, nonatomic) CBUUID *bleBatteryServiceId;
@property (readonly, nonatomic) CBUUID *bleRobotDriveServiceId;
@property (readonly, nonatomic) NSArray<CBUUID *> *bleServiceIds;

@property (readonly, nonatomic) CBUUID  *bleBatteryServiceCharId;
@property (readonly, nonatomic) NSArray<CBUUID *> *bleBatteryServiceChars;

@property (readonly, nonatomic) CBUUID *bleRobotDriveSpeedCharId;
@property (readonly, nonatomic) CBUUID *bleRobotDriveDirectionCharId;
@property (readonly, nonatomic) CBCharacteristic *bleRobotDriveSpeedChar;
@property (readonly, nonatomic) CBCharacteristic *bleRobotDriveDirectionChar;
@property (readonly, nonatomic) NSArray<CBUUID *> *bleRobotDriveChars;

@end

@implementation BLEPeripheral

/*
 * Returns singleton sharedBLEPeripheral object.
 */
+ (BLEPeripheral *) sharedBLEPeripheral {
    static BLEPeripheral *sharedPeripheral = nil;
    @synchronized (self) {
        if (sharedPeripheral == nil) {
            sharedPeripheral = [[self alloc] init];
        }
    }
    
    return sharedPeripheral;
}

/*
 * Initializes the BLEPeripheral.
 */
- (BLEPeripheral *)init {
    _blePeripheral = nil;
    
    // TODO: fill in approproiate UUIDs
    _bleBatteryServiceId = [CBUUID UUIDWithString:@""];
    _bleRobotDriveServiceId = [CBUUID UUIDWithString:@""];
    _bleServiceIds = [NSArray arrayWithObjects:_bleBatteryServiceId,
                      _bleRobotDriveServiceId, nil];
    
    _bleBatteryServiceCharId = [CBUUID UUIDWithString:@""];
    _bleBatteryServiceChars = [NSArray arrayWithObject:_bleBatteryServiceCharId];
    
    _bleRobotDriveSpeedCharId = [CBUUID UUIDWithString:@""];
    _bleRobotDriveDirectionCharId = [CBUUID UUIDWithString:@""];
    _bleRobotDriveChars = [NSArray arrayWithObjects:_bleRobotDriveSpeedCharId,
                           _bleRobotDriveDirectionCharId, nil];
    
    _bleRobotDriveService = nil;
    _bleRobotDriveCharacteristics = nil;
    _bleBatteryService = nil;
    _bleBatteryCharacteristics = nil;
    
    return self;
}

/*
 * Sets the peripheral member of the BLEPeripheral object and the peripheral's
 * delegate.
 */
- (void)setPeripheral:(CBPeripheral *)peripheral {
    _blePeripheral = peripheral;
    [_blePeripheral setDelegate:self];
}

/*
 * Discovers the peripheral's services.
 */
- (void)discoverServices {
    if (_blePeripheral != nil) {
        [_blePeripheral discoverServices:_bleServiceIds];
    }
}

/*
 * Invoked when you discover the peripheral's available services.
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(NSError *)error {
    if (error != nil) {
        NSLog(@"Error: %@", error);
        return;
    }
    
    // Discover the characteristics for both services
    NSArray<CBService *> *services = [peripheral services];
    NSUInteger numServices = [services count];
    for (NSUInteger i = 0; i < numServices; ++i) {
        CBService *service = [services objectAtIndex:i];
        NSLog(@"Service discovered: %@", service);
        
        if ([service UUID] == _bleRobotDriveServiceId) {
            _bleRobotDriveService = service;
            [peripheral discoverCharacteristics:
                _bleRobotDriveChars forService:service];
        } else {
            _bleBatteryService = service;
            [peripheral discoverCharacteristics:
                _bleBatteryServiceChars forService:service];
        }
    }
}

/*
 * Invoked when you discover the characteristics of a specified service.
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error {
    if (error != nil) {
        NSLog(@"Error: %@", error);
        return;
    }
    
    if ([service UUID] == _bleRobotDriveServiceId) {
        _bleRobotDriveCharacteristics = [service characteristics];
        
        CBCharacteristic *firstChar =
            [_bleRobotDriveCharacteristics objectAtIndex:0];
        if ([firstChar UUID] == _bleRobotDriveSpeedCharId) {
            _bleRobotDriveSpeedChar =
                [_bleRobotDriveCharacteristics objectAtIndex:0];
            
            _bleRobotDriveDirectionChar =
                [_bleRobotDriveCharacteristics objectAtIndex:1];
        } else {
            _bleRobotDriveSpeedChar =
                [_bleRobotDriveCharacteristics objectAtIndex:1];
            
            _bleRobotDriveDirectionChar =
                [_bleRobotDriveCharacteristics objectAtIndex:0];
        }
    } else {
        _bleBatteryCharacteristics = [service characteristics];
    }
    
    NSUInteger numServices = [[service characteristics] count];
    for(NSUInteger i = 0; i < numServices; ++i) {
        CBCharacteristic *characteristic =
            [[service characteristics] objectAtIndex:i];
        NSLog(@"Discovered characteristic: %@ for service %@",
              [characteristic UUID], [service UUID]);
        NSLog(@"With value: %@", [characteristic value]);
    }
}

/*
 * Returns true if peripheral has been connected to, otherwise false.
 */
- (BOOL)isConnected {
    return _blePeripheral != nil;
}

/*
 * Sets the robot's speed.
 */
- (void)setRobotDriveSpeed:(NSData *)speed {
    if ([self isConnected]) {
        [_blePeripheral writeValue:speed forCharacteristic:
         _bleRobotDriveSpeedChar type:CBCharacteristicWriteWithoutResponse];
    }
}

/*
 * Sets the robot's direction.
 */
- (void)setRobotDriveDirection:(NSData *)direction {
    if ([self isConnected]) {
        [_blePeripheral writeValue:direction forCharacteristic:
        _bleRobotDriveDirectionChar type:CBCharacteristicWriteWithoutResponse];
    }
}

@end