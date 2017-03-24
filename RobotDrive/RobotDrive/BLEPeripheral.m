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
        // TODO
    }
}

@end