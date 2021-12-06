; ModuleID = 'top.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@DIFF = constant [4 x i32] [i32 -5, i32 1, i32 5, i32 -1], align 16

; Function Attrs: norecurse nounwind uwtable
define void @top(i64 %m1_addr, i64 %m2_addr, i64 %SIZE) #0 {
entry:
  store volatile i8 0, i8* inttoptr (i64 788529664 to i8*), align 512
  store volatile i64 %m1_addr, i64* inttoptr (i64 804257793 to i64*), align 8
  store volatile i64 790626304, i64* inttoptr (i64 804257801 to i64*), align 8
  store volatile i32 36, i32* inttoptr (i64 804257809 to i32*), align 4
  store volatile i8 1, i8* inttoptr (i64 804257792 to i8*), align 1048576
  br label %while.cond

while.cond:                                       ; preds = %while.cond, %entry
  %0 = load volatile i8, i8* inttoptr (i64 804257792 to i8*), align 1048576
  %and = and i8 %0, 4
  %cmp = icmp eq i8 %and, 0
  br i1 %cmp, label %while.cond, label %while.end

while.end:                                        ; preds = %while.cond
  store volatile i64 790626304, i64* inttoptr (i64 788529665 to i64*), align 8
  store volatile i64 790626340, i64* inttoptr (i64 788529673 to i64*), align 8
  store volatile i64 %SIZE, i64* inttoptr (i64 788529681 to i64*), align 8
  br label %while.cond2

while.cond2:                                      ; preds = %while.cond2, %while.end
  %1 = load volatile i8, i8* inttoptr (i64 788529664 to i8*), align 512
  %cmp4 = icmp eq i8 %1, 0
  br i1 %cmp4, label %while.end7, label %while.cond2

while.end7:                                       ; preds = %while.cond2
  store volatile i8 1, i8* inttoptr (i64 788529664 to i8*), align 512
  br label %while.cond8

while.cond8:                                      ; preds = %while.cond8, %while.end7
  %2 = load volatile i8, i8* inttoptr (i64 788529664 to i8*), align 512
  %and10 = and i8 %2, 4
  %cmp11 = icmp eq i8 %and10, 0
  br i1 %cmp11, label %while.cond8, label %while.end14

while.end14:                                      ; preds = %while.cond8
  store volatile i8 0, i8* inttoptr (i64 788529664 to i8*), align 512
  store volatile i64 790626340, i64* inttoptr (i64 804257793 to i64*), align 8
  store volatile i64 %m2_addr, i64* inttoptr (i64 804257801 to i64*), align 8
  store volatile i32 4, i32* inttoptr (i64 804257809 to i32*), align 4
  store volatile i8 1, i8* inttoptr (i64 804257792 to i8*), align 1048576
  br label %while.cond15

while.cond15:                                     ; preds = %while.cond15, %while.end14
  %3 = load volatile i8, i8* inttoptr (i64 804257792 to i8*), align 1048576
  %and17 = and i8 %3, 4
  %cmp18 = icmp eq i8 %and17, 0
  br i1 %cmp18, label %while.cond15, label %while.end21

while.end21:                                      ; preds = %while.cond15
  ret void
}

attributes #0 = { norecurse nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.1 "}
