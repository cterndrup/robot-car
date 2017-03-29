//
//  BLECentralManager.m
//  RobotDrive
//
//  Created by COLIN TERNDRUP on 3/13/17.
//  Copyright © 2017 COLIN TERNDRUP. All rights reserved.
//

#import "BLECentralManager.h"
#import "BLEPeripheral.h"

@interface BLECentralManager ()

@property (readonly, nonatomic) CBUUID *bleBatteryServiceId;
@property (readonly, nonatomic) CBUUID *bleRobotDriveServiceId;
@property (readonly, nonatomic) NSDictionary *bleConnectOpts;

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
 * Initializes the BLECentralManager.
 */
- (BLECentralManager *)init {
    NSDictionary *initOpts = [[NSDictionary alloc] initWithObjectsAndKeys:
                          CBCentralManagerOptionShowPowerAlertKey,
                          [NSNumber numberWithBool:YES], nil];
    
    self = [super initWithDelegate:self queue:
            dispatch_get_main_queue() options:initOpts];
    
    // Initialize the CBUUID objects
    // TODO: fill in appropriate service UUIDs
    _bleBatteryServiceId = [CBUUID UUIDWithString:@""];
    _bleRobotDriveServiceId = [CBUUID UUIDWithString:@""];
    
    // Initialize connection options
    NSArray *connectOpts =
        [NSArray arrayWithObjects:
         CBConnectPeripheralOptionNotifyOnConnectionKey,
         CBConnectPeripheralOptionNotifyOnDisconnectionKey, nil];
    
    _bleConnectOpts = [NSDictionary dictionaryWithObjects:
                       [NSArray arrayWithObjects:
                        [NSNumber numberWithBool:YES],
                        [NSNumber numberWithBool:YES], nil] forKeys:
                       connectOpts];
    
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
 * successful. You typically implement this method to set the peripheral’s
 * delegate and to discover its services.
 */
- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:
    (CBPeripheral *)peripheral {
    // Set peripheral's delegate and begin discovering services
    BLEPeripheral *blePeripheral = [BLEPeripheral sharedBLEPeripheral];
    [blePeripheral setPeripheral:peripheral];
    
    NSLog(@"Connected to peripheral: %@\n", [peripheral name]);
    NSLog(@"Begin discovering peripheral's services...");
    [blePeripheral discoverServices];
}

/*
 * Invoked when a central manager fails to create a connection with a
 * peripheral.
 */
- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:
(CBPeripheral *)peripheral error:(NSError *)error {
    NSLog(@"Failed to connect to peripheral: %@\n", [peripheral name]);
    NSLog(@"Error: %@", error);
}

/*
 * Invoked when an existing connection with a peripheral is torn down.
 */
- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:
    (CBPeripheral *)peripheral error:(NSError *)error {
    NSLog(@"Disconnected from peripheral: %@\n", [peripheral name]);
}

/*
 * Invoked when a central manager discovers a peripheral while scanning.
 */
- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary<NSString *,id> *)advertisementData RSSI:(NSNumber *)RSSI {
    
    // Stop scanning
    [self stopScan];
    
    NSLog(@"Discovered peripheral: %@\n", [peripheral name]);
    NSLog(@"Peripheral RSSI: %@\n", RSSI);
    
    // delegate to alert where user has option to connect or cancel
    if ([_alertDelegate bleCentralManager:self willConnectForPeripheral:peripheral]) {
        // Create timer to fire connection timeout
        [self scheduledConnectionTimeoutWithTimerInterval:5.0 forCentralManager:
         central andPeripheral:peripheral];
        
        // Connect to peripheral
        [self connectPeripheral:peripheral options:_bleConnectOpts];
    }
}

/*
 * Scans for the robot car's Bluetooth Low Energy services with the
 * provided options.
 */
- (void)scanForPeripheralsWithOptions:(NSDictionary<NSString *,id> *)opts {
    [self scanForPeripheralsWithServices:[self getServiceUUIDs] options: opts];
}

/*
 * Returns an NSArray composed of the UUIDs of the robot car's Bluetooth
 * Low Energy services.
 */
- (NSArray *)getServiceUUIDs {
    return [NSArray arrayWithObjects:
            _bleBatteryServiceId, _bleRobotDriveServiceId, nil];
}

/*
 * Invokes the alertDelegate's corresponding method to present an alert to inform
 * the user that the connection request to the peripheral has timed out.
 */
- (void)centralManager:(CBCentralManager *)central connectionTimeoutForPeripheral:(CBPeripheral *)peripheral {
    
    [_alertDelegate bleCentralManager:self connectionToPeripheral:
     peripheral didTimeoutWithMessage:
     [NSString stringWithFormat:
      @"Connection to peripheral %@ timed out.", [peripheral name]]];
}

/*
 * Creates and returns an NSTimer object representing a Bluetooth Low Energy
 * connection request timeout. The NSTimer object is scheduled on the default
 * NSRunLoop.
 */
- (NSTimer *)scheduledConnectionTimeoutWithTimerInterval:(NSTimeInterval)ti forCentralManager:(CBCentralManager *)central andPeripheral:(CBPeripheral *)peripheral {
    
    NSMethodSignature *ms =
        [NSMethodSignature methodSignatureForSelector:
         @selector(centralManager:connectionTimeoutForPeripheral:)];
    
    NSInvocation *inv = [NSInvocation invocationWithMethodSignature:ms];
    
    [inv setArgument:&central atIndex:0];
    [inv setArgument:&peripheral atIndex:1];
    
    return [NSTimer scheduledTimerWithTimeInterval:ti invocation:inv repeats:NO];
}

@end