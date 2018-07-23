//
//  ViewController.m
//  HPCG Benchmark
//
//  Created by user142450 on 7/16/18.
//  Copyright © 2018 hpcg. All rights reserved.
//

#import "ViewController.h"
#import "main.hpp"

@interface ViewController (){
    IBOutlet UIButton *runButton;
    IBOutlet UITextField *dx;
    IBOutlet UITextField *dy;
    IBOutlet UITextField *dz;
    IBOutlet UIView *Bandwidth;
    //IBOutlet UIView *GflopsResult;
    IBOutlet UITextField *BandwidthResult;
    __weak IBOutlet UILabel *Gflops;
    //__weak IBOutlet UILabel *Gflops2;
    __weak IBOutlet UITextField *GflopsResult;
}
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    [Gflops setHidden:YES];
    [Bandwidth setHidden:YES];
    [GflopsResult setHidden:YES];
    [BandwidthResult setHidden:YES];
    dx.text=@"10";
    dy.text=@"10";
    dz.text=@"10";
}

- (IBAction)touchDown:(id)sender {
    //double *result = (double*)malloc(2*sizeof(*result));
    const char* nx = [dx.text UTF8String];
    const char* ny = [dy.text UTF8String];
    const char* nz = [dz.text UTF8String];
    double *result;
    result = hpcg(4, (char*)nx, (char*)ny, (char*)nz);
    [(id)Gflops setHidden:NO];
    [Bandwidth setHidden:NO];
    [GflopsResult setHidden:NO];
    [BandwidthResult setHidden:NO];}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
