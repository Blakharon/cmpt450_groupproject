; ModuleID = 'argmax.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@DIFF = constant [4 x i32] [i32 -5, i32 1, i32 5, i32 -1], align 16

; Function Attrs: norecurse nounwind uwtable
define void @argmax(i32* nocapture readonly %m1, i32* nocapture %m2, i32 %SIZE) #0 {
entry:
  store i32 0, i32* %m2, align 4
  %cmp1 = icmp sgt i32 %SIZE, 0
  br i1 %cmp1, label %for.body.preheader, label %for.end

for.body.preheader:                               ; preds = %entry
  %xtraiter = and i32 %SIZE, 1
  %lcmp.mod = icmp eq i32 %xtraiter, 0
  br i1 %lcmp.mod, label %for.body.preheader.split, label %for.body.prol

for.body.prol:                                    ; preds = %for.body.preheader
  %0 = load i32, i32* %m1, align 4
  %1 = load i32, i32* %m2, align 4
  %idxprom1.prol = sext i32 %1 to i64
  %arrayidx2.prol = getelementptr inbounds i32, i32* %m1, i64 %idxprom1.prol
  %2 = load i32, i32* %arrayidx2.prol, align 4
  %cmp3.prol = icmp sgt i32 %0, %2
  br i1 %cmp3.prol, label %if.then.prol, label %for.body.preheader.split

if.then.prol:                                     ; preds = %for.body.prol
  store i32 0, i32* %m2, align 4
  br label %for.body.preheader.split

for.body.preheader.split:                         ; preds = %for.body.prol, %if.then.prol, %for.body.preheader
  %indvars.iv.unr = phi i64 [ 0, %for.body.preheader ], [ 1, %if.then.prol ], [ 1, %for.body.prol ]
  %3 = icmp eq i32 %SIZE, 1
  br i1 %3, label %for.end, label %for.body.preheader3

for.body.preheader3:                              ; preds = %for.body.preheader.split
  br label %for.body

for.body:                                         ; preds = %for.body.preheader3, %for.inc.1
  %indvars.iv = phi i64 [ %indvars.iv.next.1, %for.inc.1 ], [ %indvars.iv.unr, %for.body.preheader3 ]
  %arrayidx = getelementptr inbounds i32, i32* %m1, i64 %indvars.iv
  %4 = load i32, i32* %arrayidx, align 4
  %5 = load i32, i32* %m2, align 4
  %idxprom1 = sext i32 %5 to i64
  %arrayidx2 = getelementptr inbounds i32, i32* %m1, i64 %idxprom1
  %6 = load i32, i32* %arrayidx2, align 4
  %cmp3 = icmp sgt i32 %4, %6
  br i1 %cmp3, label %if.then, label %for.inc

if.then:                                          ; preds = %for.body
  %7 = trunc i64 %indvars.iv to i32
  store i32 %7, i32* %m2, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body, %if.then
  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1
  %arrayidx.1 = getelementptr inbounds i32, i32* %m1, i64 %indvars.iv.next
  %8 = load i32, i32* %arrayidx.1, align 4
  %9 = load i32, i32* %m2, align 4
  %idxprom1.1 = sext i32 %9 to i64
  %arrayidx2.1 = getelementptr inbounds i32, i32* %m1, i64 %idxprom1.1
  %10 = load i32, i32* %arrayidx2.1, align 4
  %cmp3.1 = icmp sgt i32 %8, %10
  br i1 %cmp3.1, label %if.then.1, label %for.inc.1

for.end.loopexit:                                 ; preds = %for.inc.1
  br label %for.end

for.end:                                          ; preds = %for.end.loopexit, %for.body.preheader.split, %entry
  ret void

if.then.1:                                        ; preds = %for.inc
  %11 = trunc i64 %indvars.iv.next to i32
  store i32 %11, i32* %m2, align 4
  br label %for.inc.1

for.inc.1:                                        ; preds = %if.then.1, %for.inc
  %indvars.iv.next.1 = add nsw i64 %indvars.iv, 2
  %lftr.wideiv.1 = trunc i64 %indvars.iv.next.1 to i32
  %exitcond.1 = icmp eq i32 %lftr.wideiv.1, %SIZE
  br i1 %exitcond.1, label %for.end.loopexit, label %for.body
}

attributes #0 = { norecurse nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.1 "}
