//
//  ViewController.m
//  HPCG Benchmark
//
//  Created by user142450 on 7/16/18.
//  Copyright © 2018 hpcg. All rights reserved.
//

#import "ViewController.h"
#import "native-main.cpp"

@interface ViewController (){
    IBOutlet UIButton *runButton;
    IBOutlet UITextField *dx;
    IBOutlet UITextField *dy;
    IBOutlet UITextField *dz;
    }
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)hpcgRun {
    double* result = (double*)malloc(2*sizeof(*result));
    std::string nx = "16";

    hpcg(4, "16", "16", "16");
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
