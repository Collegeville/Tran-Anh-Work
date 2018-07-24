//
//  ViewController.m
//  HPCG Benchmark
//
//  Created by user142450 on 7/16/18.
//  Copyright © 2018 hpcg. All rights reserved.
//

#import "ViewController.h"
#import "main.hpp"
#import "pthread.h"
#import "struct.hpp"


@interface ViewController (){
}
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    progressSpin.hidden = YES;
    // Do any additional setup after loading the view, typically from a nib.
    [self addInputs];
    [self addLabels];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
    [self addInputs];
}

-(void)addInputs{
    //x Dimension
    xInput = [[UITextField alloc] initWithFrame:CGRectMake(172.5, 74, 125, 30)];
    xInput.borderStyle = UITextBorderStyleRoundedRect;
    xInput.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    [xInput setFont:[UIFont boldSystemFontOfSize:12]];
    xInput.placeholder = @"input x dimension";
    [self.view addSubview:xInput];
    xInput.delegate = self;
    
    //y Dimension
    yInput = [[UITextField alloc] initWithFrame:CGRectMake(172.5, 116, 125, 30)];
    yInput.borderStyle = UITextBorderStyleRoundedRect;
    yInput.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    [yInput setFont:[UIFont boldSystemFontOfSize:12]];
    yInput.placeholder = @"input y dimension";
    [self.view addSubview:yInput];
    yInput.delegate = self;
    
    //z Dimension
    zInput = [[UITextField alloc] initWithFrame:CGRectMake(172.5, 74, 125, 30)];
    zInput.borderStyle = UITextBorderStyleRoundedRect;
    zInput.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    [zInput setFont:[UIFont boldSystemFontOfSize:12]];
    zInput.placeholder = @"input z dimension";
    [self.view addSubview:zInput];
    zInput.delegate = self;
    
}

-(void)textFieldDidBeginEditing:(UITextField *)textField{
    NSLog(@"Text fields did begin editing");
}

-(void)textFieldDidEndEditing:(UITextField *)textField{
    NSLog(@"Text fields did end editing");
    dx = xInput.text;
    dy = yInput.text;
    dz = zInput.text;
    if([dx  isEqual: @""]){
        dx = dy;
    }
    
}

-(void)addLabels{
    //x Dimension
    xDim = [[UILabel alloc]initWithFrame:CGRectMake(75, 83.5, 96.5, 20.5)];
    xDim.numberOfLines = 0;
    xDim.textColor = [UIColor blackColor];
    xDim.backgroundColor = [UIColor clearColor];
    xDim.text = @"x Dimension";
    [self.view addSubview:xDim];
    
    //y Dimension
    yDim = [[UILabel alloc]initWithFrame:CGRectMake(75, 126, 96.5, 20.5)];
    yDim.numberOfLines = 0;
    yDim.textColor = [UIColor blackColor];
    yDim.backgroundColor = [UIColor clearColor];
    yDim.text = @"y Dimension";
    [self.view addSubview:yDim];
    
    //z Dimension
    zDim = [[UILabel alloc]initWithFrame:CGRectMake(75, 168.5, 96.5, 20.5)];
    zDim.numberOfLines = 0;
    zDim.textColor = [UIColor blackColor];
    zDim.backgroundColor = [UIColor clearColor];
    zDim.text = @"z Dimension";
    [self.view addSubview:zDim];
    
}
- (IBAction)runButton:(id)sender {
    pthread_attr_t attr;
    pthread_t posixThreadID;
    int returnVal;
    struct args *args;
    args = (struct args*)malloc(sizeof(*args));


    const char *x = [dx UTF8String];
    const char *y = [dy UTF8String];
    const char *z = [dz UTF8String];
    
    args->argc = 4;
    args->dx = (char *)x;
    args->dy = (char *)y;
    args->dz = (char *)z;
    double *result = (double *)malloc(2*sizeof(*result));
    args->result = result;
    returnVal = pthread_attr_init(&attr);
    assert(!returnVal);
    returnVal = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    assert(!returnVal);
    progressSpin.hidden = NO;
    [progressSpin startAnimating];
    int ret = pthread_create(&posixThreadID, NULL,hpcg, args);
    pthread_join(posixThreadID, NULL);
    [progressSpin stopAnimating];
    progressSpin.hidden = YES;
    NSString *gResult = [NSString stringWithFormat:@"%f", result[0]];
    NSString *bwResult = [NSString stringWithFormat:@"%f", result[1]];
    returnVal = pthread_attr_destroy(&attr);
    assert(!returnVal);
    if (ret !=0){
        Gflops.text = @"please type in valid number for matrices' dimensions";
        Gflops.hidden = NO;
    }
    
    GflopsResult.text=gResult;
    BandWidthResult.text=bwResult;
    Bandwidth.hidden = NO;
    Gflops.hidden = NO;
    GflopsResult.hidden = NO;
    BandWidthResult.hidden = NO;
    
}

@end
