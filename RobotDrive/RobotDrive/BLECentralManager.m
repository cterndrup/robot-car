//
//  BLECentralManager.m
//  RobotDrive
//
//  Created by COLIN TERNDRUP on 3/13/17.
//  Copyright © 2017 COLIN TERNDRUP. All rights reserved.
//

#import "BLECentralManager.h"

@interface BLECentralManager ()


@end

@implementation BLECentralManager

/*
 * Creates and returns a shared Bluetooth LE Central Manager
 */
+ (BLECentralManager *)sharedBLECentralManager {
    static BLECentralManager *sharedCentralManager = nil;
    @synchronized (self) {
        if (sharedCentralManager == nil) {
            sharedCentralManager = [[self alloc] init];
        }
    }
    
     return sharedCentralManager;
}

/*
 * Initializes the BLECentralManager
 */
- (BLECentralManager *)init {
    NSDictionary *opts = [[NSDictionary alloc] initWithObjectsAndKeys:
                          CBCentralManagerOptionShowPowerAlertKey,
                          [NSNumber numberWithBool:YES], nil];
    
    self = [super initWithDelegate:self queue:
            dispatch_get_main_queue() options:opts];
    return self;
}

/*
 * Invoked when the central manager's state is updated.
 */
- (void)centralManagerDidUpdateState:(CBCentralManager *)central {
    // TODO
}


/*
 * Invoked when a connection is successfully created with a peripheral.
 *
 * @Discussion 
 * This method is invoked when a call to connectPeripheral:options: is
 * successful.You typically implement this method to set the peripheral’s
 * delegate and to discover its services.
 */
- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:
    (CBPeripheral *)peripheral {
    // TODO
}

/*
 * Invoked when an existing connection with a peripheral is torn down.
 */
- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:
    (CBPeripheral *)peripheral error:(NSError *)error {
    // TODO
}

/*
 * Invoked when a central manager fails to create a connection with a 
 * peripheral.
 */
- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:
    (CBPeripheral *)peripheral error:(NSError *)error {
    // TODO
}

@end