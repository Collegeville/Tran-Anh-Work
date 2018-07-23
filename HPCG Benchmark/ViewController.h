//
//  ViewController.h
//  HPCG Benchmark
//
//  Created by user142450 on 7/16/18.
//  Copyright © 2018 hpcg. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController<UITextFieldDelegate>
{
    IBOutlet UILabel *xDim;
    IBOutlet UILabel *yDim;
    IBOutlet UILabel *zDim;
    IBOutlet UILabel *Gflops;
    IBOutlet UILabel *Bandwidth;
    IBOutlet UITextField *zInput;
    IBOutlet UITextField *xInput;
    IBOutlet UITextField *yInput;
    NSString *dx;
    __weak IBOutlet UITextField *BandwidthResult;
    __weak IBOutlet UITextField *GflopsResult;
    NSString *dy;
    NSString *dz;
     __weak IBOutlet UIButton *button;
}
- (IBAction)runButton:(id)sender;


@end

