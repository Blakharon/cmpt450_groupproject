; ModuleID = 'top.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: norecurse nounwind uwtable
define void @top(i64 %heights, i64 %excess_flows, i64 %nodes_curr_capacities, i64 %nodes_capacities, i64 %res_curr_capacities, i64 %source_height, i64 %source_excess_flow, i64 %source_curr_capacities, i64 %source_capacities, i64 %sink_height, i64 %sink_excess_flow, i64 %res_source_curr_capacities) #0 {
entry:
  store volatile i8 0, i8* inttoptr (i64 788529664 to i8*), align 512
  store volatile i64 %heights, i64* inttoptr (i64 788529665 to i64*), align 8
  store volatile i64 %excess_flows, i64* inttoptr (i64 788529673 to i64*), align 8
  store volatile i64 %nodes_curr_capacities, i64* inttoptr (i64 788529681 to i64*), align 8
  store volatile i64 %nodes_capacities, i64* inttoptr (i64 788529689 to i64*), align 8
  store volatile i64 %res_curr_capacities, i64* inttoptr (i64 788529697 to i64*), align 8
  store volatile i64 %source_height, i64* inttoptr (i64 788529705 to i64*), align 8
  store volatile i64 %source_excess_flow, i64* inttoptr (i64 788529713 to i64*), align 8
  store volatile i64 %source_curr_capacities, i64* inttoptr (i64 788529721 to i64*), align 8
  store volatile i64 %source_capacities, i64* inttoptr (i64 788529729 to i64*), align 8
  store volatile i64 %sink_height, i64* inttoptr (i64 788529737 to i64*), align 8
  store volatile i64 %sink_excess_flow, i64* inttoptr (i64 788529745 to i64*), align 8
  store volatile i64 %res_source_curr_capacities, i64* inttoptr (i64 788529753 to i64*), align 8
  store volatile i8 1, i8* inttoptr (i64 788529664 to i8*), align 512
  br label %while.cond

while.cond:                                       ; preds = %while.cond, %entry
  %0 = load volatile i8, i8* inttoptr (i64 788529664 to i8*), align 512
  %and = and i8 %0, 4
  %cmp = icmp eq i8 %and, 0
  br i1 %cmp, label %while.cond, label %while.end

while.end:                                        ; preds = %while.cond
  store volatile i8 0, i8* inttoptr (i64 788529664 to i8*), align 512
  ret void
}

attributes #0 = { norecurse nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.1 "}
