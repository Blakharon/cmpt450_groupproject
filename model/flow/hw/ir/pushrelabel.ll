; ModuleID = 'pushrelabel.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: norecurse nounwind uwtable
define void @pushrelabel(i32* nocapture %heights, i32* nocapture %excess_flows, i32* nocapture %nodes_curr_capacities, i32* nocapture readonly %nodes_capacities, i32* nocapture %res_curr_capacities, i32* nocapture %source_height, i32* nocapture %source_excess_flow, i32* nocapture %source_curr_capacities, i32* nocapture readonly %source_capacities, i32* nocapture readonly %sink_height, i32* nocapture %sink_excess_flow, i32* nocapture %res_source_curr_capacities) #0 {
entry:
  store i32 27, i32* %source_height, align 4
  br label %for.body

for.body:                                         ; preds = %for.body, %entry
  %indvars.iv55 = phi i64 [ 0, %entry ], [ %indvars.iv.next56, %for.body ]
  %arrayidx1 = getelementptr inbounds i32, i32* %source_capacities, i64 %indvars.iv55
  %0 = load i32, i32* %arrayidx1, align 4
  %arrayidx3 = getelementptr inbounds i32, i32* %source_curr_capacities, i64 %indvars.iv55
  store i32 %0, i32* %arrayidx3, align 4
  %1 = load i32, i32* %arrayidx1, align 4
  %arrayidx7 = getelementptr inbounds i32, i32* %res_source_curr_capacities, i64 %indvars.iv55
  store i32 %1, i32* %arrayidx7, align 4
  %2 = load i32, i32* %arrayidx1, align 4
  %arrayidx11 = getelementptr inbounds i32, i32* %excess_flows, i64 %indvars.iv55
  store i32 %2, i32* %arrayidx11, align 4
  %indvars.iv.next56 = add nuw nsw i64 %indvars.iv55, 1
  %exitcond57 = icmp eq i64 %indvars.iv.next56, 25
  br i1 %exitcond57, label %for.body15, label %for.body

for.body15:                                       ; preds = %for.body
  %3 = load i32, i32* %excess_flows, align 4
  %cmp18 = icmp sgt i32 %3, 0
  br i1 %cmp18, label %while.body.preheader, label %if.end

if.end:                                           ; preds = %for.body15
  %arrayidx17.1 = getelementptr inbounds i32, i32* %excess_flows, i64 1
  %4 = load i32, i32* %arrayidx17.1, align 4
  %cmp18.1 = icmp sgt i32 %4, 0
  br i1 %cmp18.1, label %while.body.preheader, label %if.end.1

while.body.preheader:                             ; preds = %for.body15, %if.end, %if.end.1, %if.end.2, %if.end.3, %if.end.4, %if.end.5, %if.end.6, %if.end.7, %if.end.8, %if.end.9, %if.end.10, %if.end.11, %if.end.12, %if.end.13, %if.end.14, %if.end.15, %if.end.16, %if.end.17, %if.end.18, %if.end.19, %if.end.20, %if.end.21, %if.end.22, %if.end.23
  %node.334.ph = phi i32 [ 24, %if.end.23 ], [ 23, %if.end.22 ], [ 22, %if.end.21 ], [ 21, %if.end.20 ], [ 20, %if.end.19 ], [ 19, %if.end.18 ], [ 18, %if.end.17 ], [ 17, %if.end.16 ], [ 16, %if.end.15 ], [ 15, %if.end.14 ], [ 14, %if.end.13 ], [ 13, %if.end.12 ], [ 12, %if.end.11 ], [ 11, %if.end.10 ], [ 10, %if.end.9 ], [ 9, %if.end.8 ], [ 8, %if.end.7 ], [ 7, %if.end.6 ], [ 6, %if.end.5 ], [ 5, %if.end.4 ], [ 4, %if.end.3 ], [ 3, %if.end.2 ], [ 2, %if.end.1 ], [ 1, %if.end ], [ 0, %for.body15 ]
  br label %while.body

while.cond.loopexit:                              ; preds = %for.body409, %if.end414
  %node.3.ph = phi i32 [ %51, %for.body409 ], [ %.node.4, %if.end414 ]
  %cmp25 = icmp eq i32 %node.3.ph, -1
  br i1 %cmp25, label %while.end.loopexit, label %while.body

while.body:                                       ; preds = %while.body.preheader, %while.cond.loopexit
  %node.334 = phi i32 [ %node.3.ph, %while.cond.loopexit ], [ %node.334.ph, %while.body.preheader ]
  %mul = mul nsw i32 %node.334, 5
  %add = add nsw i32 %mul, 4
  %idxprom26 = sext i32 %add to i64
  %arrayidx27 = getelementptr inbounds i32, i32* %nodes_curr_capacities, i64 %idxprom26
  %5 = load i32, i32* %arrayidx27, align 4
  %arrayidx31 = getelementptr inbounds i32, i32* %nodes_capacities, i64 %idxprom26
  %6 = load i32, i32* %arrayidx31, align 4
  %cmp32 = icmp sgt i32 %6, %5
  br i1 %cmp32, label %if.then33, label %for.body68

if.then33:                                        ; preds = %while.body
  %sub = sub nsw i32 %6, %5
  %idxprom42 = sext i32 %node.334 to i64
  %arrayidx43 = getelementptr inbounds i32, i32* %excess_flows, i64 %idxprom42
  %7 = load i32, i32* %arrayidx43, align 4
  %cmp44 = icmp sgt i32 %7, %sub
  %sub. = select i1 %cmp44, i32 %sub, i32 %7
  %sub51 = sub nsw i32 %7, %sub.
  store i32 %sub51, i32* %arrayidx43, align 4
  %8 = load i32, i32* %sink_excess_flow, align 4
  %add53 = add nsw i32 %8, %sub.
  store i32 %add53, i32* %sink_excess_flow, align 4
  %9 = load i32, i32* %arrayidx27, align 4
  %add58 = add nsw i32 %9, %sub.
  store i32 %add58, i32* %arrayidx27, align 4
  %cmp59 = icmp sgt i32 %sub., 0
  br i1 %cmp59, label %for.body409.preheader, label %for.body68

for.body68:                                       ; preds = %while.body, %if.then33
  %sub101 = add nsw i32 %node.334, -1
  %idxprom107 = sext i32 %node.334 to i64
  %arrayidx108 = getelementptr inbounds i32, i32* %heights, i64 %idxprom107
  %sub91 = add nsw i32 %node.334, -5
  %add95 = add nsw i32 %node.334, 1
  %add99 = add nsw i32 %node.334, 5
  %10 = sext i32 %mul to i64
  %arrayidx72 = getelementptr inbounds i32, i32* %nodes_capacities, i64 %10
  %11 = load i32, i32* %arrayidx72, align 4
  %cmp73 = icmp eq i32 %11, -1
  br i1 %cmp73, label %for.inc158, label %if.end76

if.end76:                                         ; preds = %for.body68
  %arrayidx80 = getelementptr inbounds i32, i32* %nodes_curr_capacities, i64 %10
  %12 = load i32, i32* %arrayidx80, align 4
  %cmp85 = icmp eq i32 %12, %11
  br i1 %cmp85, label %for.inc158, label %if.end104

if.end104:                                        ; preds = %if.end76
  %idxprom105 = sext i32 %sub91 to i64
  %arrayidx106 = getelementptr inbounds i32, i32* %heights, i64 %idxprom105
  %13 = load i32, i32* %arrayidx106, align 4
  %14 = load i32, i32* %arrayidx108, align 4
  %cmp109 = icmp sgt i32 %14, %13
  br i1 %cmp109, label %if.then110, label %for.inc158

if.then110:                                       ; preds = %if.end104.3, %if.end104.2, %if.end104.1, %if.end104
  %idxprom105.lcssa = phi i64 [ %idxprom105, %if.end104 ], [ %idxprom105.1, %if.end104.1 ], [ %idxprom105.2, %if.end104.2 ], [ %idxprom105.3, %if.end104.3 ]
  %neighbour_idx.2.lcssa = phi i32 [ %sub91, %if.end104 ], [ %add95, %if.end104.1 ], [ %add99, %if.end104.2 ], [ %sub101, %if.end104.3 ]
  %arrayidx80.lcssa = phi i32* [ %arrayidx80, %if.end104 ], [ %arrayidx80.1, %if.end104.1 ], [ %arrayidx80.2, %if.end104.2 ], [ %arrayidx80.3, %if.end104.3 ]
  %arrayidx72.lcssa = phi i32* [ %arrayidx72, %if.end104 ], [ %arrayidx72.1, %if.end104.1 ], [ %arrayidx72.2, %if.end104.2 ], [ %arrayidx72.3, %if.end104.3 ]
  %i65.020.lcssa.wide = phi i32 [ 2, %if.end104 ], [ 3, %if.end104.1 ], [ 0, %if.end104.2 ], [ 1, %if.end104.3 ]
  %15 = load i32, i32* %arrayidx72.lcssa, align 4
  %16 = load i32, i32* %arrayidx80.lcssa, align 4
  %sub121 = sub nsw i32 %15, %16
  %arrayidx123 = getelementptr inbounds i32, i32* %excess_flows, i64 %idxprom107
  %17 = load i32, i32* %arrayidx123, align 4
  %cmp124 = icmp sgt i32 %17, %sub121
  %sub121. = select i1 %cmp124, i32 %sub121, i32 %17
  %sub132 = sub nsw i32 %17, %sub121.
  store i32 %sub132, i32* %arrayidx123, align 4
  %arrayidx134 = getelementptr inbounds i32, i32* %excess_flows, i64 %idxprom105.lcssa
  %18 = load i32, i32* %arrayidx134, align 4
  %add135 = add nsw i32 %18, %sub121.
  store i32 %add135, i32* %arrayidx134, align 4
  %19 = load i32, i32* %arrayidx80.lcssa, align 4
  %add140 = add nsw i32 %19, %sub121.
  store i32 %add140, i32* %arrayidx80.lcssa, align 4
  %mul141 = mul nsw i32 %neighbour_idx.2.lcssa, 5
  %add142 = add nsw i32 %mul141, %i65.020.lcssa.wide
  %idxprom143 = sext i32 %add142 to i64
  %arrayidx144 = getelementptr inbounds i32, i32* %res_curr_capacities, i64 %idxprom143
  %20 = load i32, i32* %arrayidx144, align 4
  %cmp145 = icmp eq i32 %20, -1
  br i1 %cmp145, label %if.then146, label %if.end151

if.then146:                                       ; preds = %if.then110
  store i32 0, i32* %arrayidx144, align 4
  br label %if.end151

if.end151:                                        ; preds = %if.then146, %if.then110
  %21 = load i32, i32* %arrayidx144, align 4
  %add156 = add nsw i32 %21, %sub121.
  store i32 %add156, i32* %arrayidx144, align 4
  br label %for.body409.preheader

for.inc158:                                       ; preds = %if.end76, %for.body68, %if.end104
  %continue_count.1 = phi i32 [ 0, %if.end104 ], [ 1, %for.body68 ], [ 1, %if.end76 ]
  %22 = add nsw i64 %10, 1
  %arrayidx72.1 = getelementptr inbounds i32, i32* %nodes_capacities, i64 %22
  %23 = load i32, i32* %arrayidx72.1, align 4
  %cmp73.1 = icmp eq i32 %23, -1
  br i1 %cmp73.1, label %if.then74.1, label %if.end76.1

for.body169:                                      ; preds = %for.inc158.3
  %sub191 = add nsw i32 %node.334, -1
  %idxprom206 = sext i32 %node.334 to i64
  %arrayidx207 = getelementptr inbounds i32, i32* %heights, i64 %idxprom206
  %sub181 = add nsw i32 %node.334, -5
  %add185 = add nsw i32 %node.334, 1
  %add189 = add nsw i32 %node.334, 5
  %24 = sext i32 %mul to i64
  %arrayidx173 = getelementptr inbounds i32, i32* %nodes_capacities, i64 %24
  %25 = load i32, i32* %arrayidx173, align 4
  %cmp174 = icmp eq i32 %25, -1
  br i1 %cmp174, label %for.inc236, label %if.end194

if.end194:                                        ; preds = %for.body169
  %arrayidx198 = getelementptr inbounds i32, i32* %res_curr_capacities, i64 %24
  %26 = load i32, i32* %arrayidx198, align 4
  %cmp199 = icmp slt i32 %26, 1
  br i1 %cmp199, label %for.inc236, label %if.end202

if.end202:                                        ; preds = %if.end194
  %idxprom204 = sext i32 %sub181 to i64
  %arrayidx205 = getelementptr inbounds i32, i32* %heights, i64 %idxprom204
  %27 = load i32, i32* %arrayidx205, align 4
  %28 = load i32, i32* %arrayidx207, align 4
  %cmp208 = icmp sgt i32 %28, %27
  br i1 %cmp208, label %if.then209, label %for.inc236

if.then209:                                       ; preds = %if.end202.3, %if.end202.2, %if.end202.1, %if.end202
  %idxprom204.lcssa = phi i64 [ %idxprom204, %if.end202 ], [ %idxprom204.1, %if.end202.1 ], [ %idxprom204.2, %if.end202.2 ], [ %idxprom204.3, %if.end202.3 ]
  %.lcssa = phi i32 [ %26, %if.end202 ], [ %65, %if.end202.1 ], [ %70, %if.end202.2 ], [ %75, %if.end202.3 ]
  %arrayidx198.lcssa = phi i32* [ %arrayidx198, %if.end202 ], [ %arrayidx198.1, %if.end202.1 ], [ %arrayidx198.2, %if.end202.2 ], [ %arrayidx198.3, %if.end202.3 ]
  %arrayidx217 = getelementptr inbounds i32, i32* %excess_flows, i64 %idxprom206
  %29 = load i32, i32* %arrayidx217, align 4
  %cmp218 = icmp sgt i32 %29, %.lcssa
  %. = select i1 %cmp218, i32 %.lcssa, i32 %29
  %sub226 = sub nsw i32 %29, %.
  store i32 %sub226, i32* %arrayidx217, align 4
  %arrayidx228 = getelementptr inbounds i32, i32* %excess_flows, i64 %idxprom204.lcssa
  %30 = load i32, i32* %arrayidx228, align 4
  %add229 = add nsw i32 %30, %.
  store i32 %add229, i32* %arrayidx228, align 4
  %31 = load i32, i32* %arrayidx198.lcssa, align 4
  %sub234 = sub nsw i32 %31, %.
  store i32 %sub234, i32* %arrayidx198.lcssa, align 4
  br label %for.body409.preheader

for.inc236:                                       ; preds = %if.end194, %for.body169, %if.end202
  %continue_count.4 = phi i32 [ 0, %if.end202 ], [ 1, %for.body169 ], [ 1, %if.end194 ]
  %32 = add nsw i64 %24, 1
  %arrayidx173.1 = getelementptr inbounds i32, i32* %nodes_capacities, i64 %32
  %33 = load i32, i32* %arrayidx173.1, align 4
  %cmp174.1 = icmp eq i32 %33, -1
  br i1 %cmp174.1, label %if.then175.1, label %if.end194.1

if.end240:                                        ; preds = %if.end194.3, %for.inc236.2
  %cmp243 = icmp eq i32 %continue_count.4.2, 3
  br i1 %cmp243, label %if.then244, label %if.then271

if.then244:                                       ; preds = %if.end240
  %idxprom247 = sext i32 %node.334 to i64
  %arrayidx248 = getelementptr inbounds i32, i32* %res_source_curr_capacities, i64 %idxprom247
  %34 = load i32, i32* %arrayidx248, align 4
  %arrayidx250 = getelementptr inbounds i32, i32* %excess_flows, i64 %idxprom247
  %35 = load i32, i32* %arrayidx250, align 4
  %cmp251 = icmp sgt i32 %35, %34
  %.15 = select i1 %cmp251, i32 %34, i32 %35
  %sub259 = sub nsw i32 %35, %.15
  store i32 %sub259, i32* %arrayidx250, align 4
  %36 = load i32, i32* %source_excess_flow, align 4
  %add261 = add nsw i32 %36, %.15
  store i32 %add261, i32* %source_excess_flow, align 4
  %37 = load i32, i32* %arrayidx248, align 4
  %sub264 = sub nsw i32 %37, %.15
  store i32 %sub264, i32* %arrayidx248, align 4
  %cmp265 = icmp sgt i32 %.15, 0
  br i1 %cmp265, label %for.body409.preheader, label %if.then271

if.then271:                                       ; preds = %if.end104.3, %if.end202.3, %for.inc158.3, %if.end240, %if.then244
  %38 = load i32, i32* %arrayidx27, align 4
  %39 = load i32, i32* %arrayidx31, align 4
  %cmp281 = icmp eq i32 %38, %39
  br i1 %cmp281, label %if.end310, label %if.then282

if.then282:                                       ; preds = %if.then271
  %40 = load i32, i32* %sink_height, align 4
  %add284 = add nsw i32 %40, 1
  %idxprom285 = sext i32 %node.334 to i64
  %arrayidx286 = getelementptr inbounds i32, i32* %heights, i64 %idxprom285
  store i32 %add284, i32* %arrayidx286, align 4
  br label %for.body409.preheader

if.end310:                                        ; preds = %if.then271
  %sub307 = add nsw i32 %node.334, -1
  %idxprom338 = sext i32 %node.334 to i64
  %arrayidx339 = getelementptr inbounds i32, i32* %heights, i64 %idxprom338
  %sub297 = add nsw i32 %node.334, -5
  %add301 = add nsw i32 %node.334, 1
  %add305 = add nsw i32 %node.334, 5
  %41 = sext i32 %mul to i64
  %arrayidx314 = getelementptr inbounds i32, i32* %nodes_capacities, i64 %41
  %42 = load i32, i32* %arrayidx314, align 4
  %cmp315 = icmp eq i32 %42, -1
  br i1 %cmp315, label %if.end310.1, label %if.end318

if.end318:                                        ; preds = %if.end310
  %arrayidx322 = getelementptr inbounds i32, i32* %nodes_curr_capacities, i64 %41
  %43 = load i32, i32* %arrayidx322, align 4
  %cmp327 = icmp eq i32 %43, %42
  br i1 %cmp327, label %if.end310.1, label %if.end330

if.end330:                                        ; preds = %if.end318
  %idxprom331 = sext i32 %sub297 to i64
  %arrayidx332 = getelementptr inbounds i32, i32* %heights, i64 %idxprom331
  %44 = load i32, i32* %arrayidx332, align 4
  %cmp333 = icmp slt i32 %44, 999999999
  br i1 %cmp333, label %if.then334, label %if.end310.1

if.then334:                                       ; preds = %if.end330
  %add337 = add nsw i32 %44, 1
  store i32 %add337, i32* %arrayidx339, align 4
  br label %if.end310.1

if.end366:                                        ; preds = %for.inc341.3
  %sub363 = add nsw i32 %node.334, -1
  %idxprom390 = sext i32 %node.334 to i64
  %arrayidx391 = getelementptr inbounds i32, i32* %heights, i64 %idxprom390
  %sub353 = add nsw i32 %node.334, -5
  %add357 = add nsw i32 %node.334, 1
  %add361 = add nsw i32 %node.334, 5
  %45 = sext i32 %mul to i64
  %arrayidx370 = getelementptr inbounds i32, i32* %nodes_capacities, i64 %45
  %46 = load i32, i32* %arrayidx370, align 4
  %cmp371 = icmp eq i32 %46, -1
  br i1 %cmp371, label %if.end366.1, label %if.end374

if.end374:                                        ; preds = %if.end366
  %arrayidx378 = getelementptr inbounds i32, i32* %res_curr_capacities, i64 %45
  %47 = load i32, i32* %arrayidx378, align 4
  %cmp379 = icmp slt i32 %47, 1
  br i1 %cmp379, label %if.end366.1, label %if.end382

if.end382:                                        ; preds = %if.end374
  %idxprom383 = sext i32 %sub353 to i64
  %arrayidx384 = getelementptr inbounds i32, i32* %heights, i64 %idxprom383
  %48 = load i32, i32* %arrayidx384, align 4
  %cmp385 = icmp slt i32 %48, %min_height.2.2
  br i1 %cmp385, label %if.then386, label %if.end366.1

if.then386:                                       ; preds = %if.end382
  %add389 = add nsw i32 %48, 1
  store i32 %add389, i32* %arrayidx391, align 4
  br label %if.end366.1

if.then398:                                       ; preds = %for.inc393.3
  %49 = load i32, i32* %source_height, align 4
  %add400 = add nsw i32 %49, 1
  %idxprom401 = sext i32 %node.334 to i64
  %arrayidx402 = getelementptr inbounds i32, i32* %heights, i64 %idxprom401
  store i32 %add400, i32* %arrayidx402, align 4
  br label %for.body409.preheader

for.body409.preheader:                            ; preds = %if.then282, %if.then398, %for.inc393.3, %if.then209, %if.end151, %if.then33, %if.then244, %for.inc341.3, %if.then334.3, %if.end330.3, %if.then386.3, %if.end382.3
  br label %for.body409

for.body409:                                      ; preds = %for.body409.preheader, %if.end414
  %indvars.iv51 = phi i64 [ %indvars.iv.next52, %if.end414 ], [ 0, %for.body409.preheader ]
  %node.431 = phi i32 [ %.node.4, %if.end414 ], [ %node.334, %for.body409.preheader ]
  %arrayidx411 = getelementptr inbounds i32, i32* %excess_flows, i64 %indvars.iv51
  %50 = load i32, i32* %arrayidx411, align 4
  %cmp412 = icmp sgt i32 %50, 0
  %51 = trunc i64 %indvars.iv51 to i32
  br i1 %cmp412, label %while.cond.loopexit, label %if.end414

if.end414:                                        ; preds = %for.body409
  %cmp415 = icmp eq i64 %indvars.iv51, 24
  %.node.4 = select i1 %cmp415, i32 -1, i32 %node.431
  %indvars.iv.next52 = add nuw nsw i64 %indvars.iv51, 1
  %cmp408 = icmp slt i64 %indvars.iv.next52, 25
  br i1 %cmp408, label %for.body409, label %while.cond.loopexit

while.end.loopexit:                               ; preds = %while.cond.loopexit
  br label %while.end

while.end:                                        ; preds = %while.end.loopexit, %if.end.23
  ret void

if.end76.1:                                       ; preds = %for.inc158
  %arrayidx80.1 = getelementptr inbounds i32, i32* %nodes_curr_capacities, i64 %22
  %52 = load i32, i32* %arrayidx80.1, align 4
  %cmp85.1 = icmp eq i32 %52, %23
  br i1 %cmp85.1, label %if.then86.1, label %if.end104.1

if.end104.1:                                      ; preds = %if.end76.1
  %idxprom105.1 = sext i32 %add95 to i64
  %arrayidx106.1 = getelementptr inbounds i32, i32* %heights, i64 %idxprom105.1
  %53 = load i32, i32* %arrayidx106.1, align 4
  %54 = load i32, i32* %arrayidx108, align 4
  %cmp109.1 = icmp sgt i32 %54, %53
  br i1 %cmp109.1, label %if.then110, label %for.inc158.1

if.then86.1:                                      ; preds = %if.end76.1
  %inc87.1 = add nuw nsw i32 %continue_count.1, 1
  br label %for.inc158.1

if.then74.1:                                      ; preds = %for.inc158
  %inc75.1 = add nuw nsw i32 %continue_count.1, 1
  br label %for.inc158.1

for.inc158.1:                                     ; preds = %if.then74.1, %if.then86.1, %if.end104.1
  %continue_count.1.1 = phi i32 [ %inc75.1, %if.then74.1 ], [ %inc87.1, %if.then86.1 ], [ %continue_count.1, %if.end104.1 ]
  %55 = add nsw i64 %10, 2
  %arrayidx72.2 = getelementptr inbounds i32, i32* %nodes_capacities, i64 %55
  %56 = load i32, i32* %arrayidx72.2, align 4
  %cmp73.2 = icmp eq i32 %56, -1
  br i1 %cmp73.2, label %if.then74.2, label %if.end76.2

if.end76.2:                                       ; preds = %for.inc158.1
  %arrayidx80.2 = getelementptr inbounds i32, i32* %nodes_curr_capacities, i64 %55
  %57 = load i32, i32* %arrayidx80.2, align 4
  %cmp85.2 = icmp eq i32 %57, %56
  br i1 %cmp85.2, label %if.then86.2, label %if.end104.2

if.end104.2:                                      ; preds = %if.end76.2
  %idxprom105.2 = sext i32 %add99 to i64
  %arrayidx106.2 = getelementptr inbounds i32, i32* %heights, i64 %idxprom105.2
  %58 = load i32, i32* %arrayidx106.2, align 4
  %59 = load i32, i32* %arrayidx108, align 4
  %cmp109.2 = icmp sgt i32 %59, %58
  br i1 %cmp109.2, label %if.then110, label %for.inc158.2

if.then86.2:                                      ; preds = %if.end76.2
  %inc87.2 = add nsw i32 %continue_count.1.1, 1
  br label %for.inc158.2

if.then74.2:                                      ; preds = %for.inc158.1
  %inc75.2 = add nsw i32 %continue_count.1.1, 1
  br label %for.inc158.2

for.inc158.2:                                     ; preds = %if.then74.2, %if.then86.2, %if.end104.2
  %continue_count.1.2 = phi i32 [ %inc75.2, %if.then74.2 ], [ %inc87.2, %if.then86.2 ], [ %continue_count.1.1, %if.end104.2 ]
  %60 = add nsw i64 %10, 3
  %arrayidx72.3 = getelementptr inbounds i32, i32* %nodes_capacities, i64 %60
  %61 = load i32, i32* %arrayidx72.3, align 4
  %cmp73.3 = icmp eq i32 %61, -1
  br i1 %cmp73.3, label %for.inc158.3, label %if.end76.3

if.end76.3:                                       ; preds = %for.inc158.2
  %arrayidx80.3 = getelementptr inbounds i32, i32* %nodes_curr_capacities, i64 %60
  %62 = load i32, i32* %arrayidx80.3, align 4
  %cmp85.3 = icmp eq i32 %62, %61
  br i1 %cmp85.3, label %for.inc158.3, label %if.end104.3

if.end104.3:                                      ; preds = %if.end76.3
  %idxprom105.3 = sext i32 %sub101 to i64
  %arrayidx106.3 = getelementptr inbounds i32, i32* %heights, i64 %idxprom105.3
  %63 = load i32, i32* %arrayidx106.3, align 4
  %64 = load i32, i32* %arrayidx108, align 4
  %cmp109.3 = icmp sgt i32 %64, %63
  br i1 %cmp109.3, label %if.then110, label %if.then271

for.inc158.3:                                     ; preds = %if.end76.3, %for.inc158.2
  %cmp164 = icmp eq i32 %continue_count.1.2, 3
  br i1 %cmp164, label %for.body169, label %if.then271

if.end194.1:                                      ; preds = %for.inc236
  %arrayidx198.1 = getelementptr inbounds i32, i32* %res_curr_capacities, i64 %32
  %65 = load i32, i32* %arrayidx198.1, align 4
  %cmp199.1 = icmp slt i32 %65, 1
  br i1 %cmp199.1, label %if.then200.1, label %if.end202.1

if.end202.1:                                      ; preds = %if.end194.1
  %idxprom204.1 = sext i32 %add185 to i64
  %arrayidx205.1 = getelementptr inbounds i32, i32* %heights, i64 %idxprom204.1
  %66 = load i32, i32* %arrayidx205.1, align 4
  %67 = load i32, i32* %arrayidx207, align 4
  %cmp208.1 = icmp sgt i32 %67, %66
  br i1 %cmp208.1, label %if.then209, label %for.inc236.1

if.then200.1:                                     ; preds = %if.end194.1
  %inc201.1 = add nuw nsw i32 %continue_count.4, 1
  br label %for.inc236.1

if.then175.1:                                     ; preds = %for.inc236
  %inc176.1 = add nuw nsw i32 %continue_count.4, 1
  br label %for.inc236.1

for.inc236.1:                                     ; preds = %if.then175.1, %if.then200.1, %if.end202.1
  %continue_count.4.1 = phi i32 [ %inc176.1, %if.then175.1 ], [ %inc201.1, %if.then200.1 ], [ %continue_count.4, %if.end202.1 ]
  %68 = add nsw i64 %24, 2
  %arrayidx173.2 = getelementptr inbounds i32, i32* %nodes_capacities, i64 %68
  %69 = load i32, i32* %arrayidx173.2, align 4
  %cmp174.2 = icmp eq i32 %69, -1
  br i1 %cmp174.2, label %if.then175.2, label %if.end194.2

if.end194.2:                                      ; preds = %for.inc236.1
  %arrayidx198.2 = getelementptr inbounds i32, i32* %res_curr_capacities, i64 %68
  %70 = load i32, i32* %arrayidx198.2, align 4
  %cmp199.2 = icmp slt i32 %70, 1
  br i1 %cmp199.2, label %if.then200.2, label %if.end202.2

if.end202.2:                                      ; preds = %if.end194.2
  %idxprom204.2 = sext i32 %add189 to i64
  %arrayidx205.2 = getelementptr inbounds i32, i32* %heights, i64 %idxprom204.2
  %71 = load i32, i32* %arrayidx205.2, align 4
  %72 = load i32, i32* %arrayidx207, align 4
  %cmp208.2 = icmp sgt i32 %72, %71
  br i1 %cmp208.2, label %if.then209, label %for.inc236.2

if.then200.2:                                     ; preds = %if.end194.2
  %inc201.2 = add nsw i32 %continue_count.4.1, 1
  br label %for.inc236.2

if.then175.2:                                     ; preds = %for.inc236.1
  %inc176.2 = add nsw i32 %continue_count.4.1, 1
  br label %for.inc236.2

for.inc236.2:                                     ; preds = %if.then175.2, %if.then200.2, %if.end202.2
  %continue_count.4.2 = phi i32 [ %inc176.2, %if.then175.2 ], [ %inc201.2, %if.then200.2 ], [ %continue_count.4.1, %if.end202.2 ]
  %73 = add nsw i64 %24, 3
  %arrayidx173.3 = getelementptr inbounds i32, i32* %nodes_capacities, i64 %73
  %74 = load i32, i32* %arrayidx173.3, align 4
  %cmp174.3 = icmp eq i32 %74, -1
  br i1 %cmp174.3, label %if.end240, label %if.end194.3

if.end194.3:                                      ; preds = %for.inc236.2
  %arrayidx198.3 = getelementptr inbounds i32, i32* %res_curr_capacities, i64 %73
  %75 = load i32, i32* %arrayidx198.3, align 4
  %cmp199.3 = icmp slt i32 %75, 1
  br i1 %cmp199.3, label %if.end240, label %if.end202.3

if.end202.3:                                      ; preds = %if.end194.3
  %idxprom204.3 = sext i32 %sub191 to i64
  %arrayidx205.3 = getelementptr inbounds i32, i32* %heights, i64 %idxprom204.3
  %76 = load i32, i32* %arrayidx205.3, align 4
  %77 = load i32, i32* %arrayidx207, align 4
  %cmp208.3 = icmp sgt i32 %77, %76
  br i1 %cmp208.3, label %if.then209, label %if.then271

if.end310.1:                                      ; preds = %if.end318, %if.end310, %if.end330, %if.then334
  %min_height.2 = phi i32 [ %44, %if.then334 ], [ 999999999, %if.end330 ], [ 999999999, %if.end310 ], [ 999999999, %if.end318 ]
  %continue_count272.1 = phi i32 [ 0, %if.then334 ], [ 0, %if.end330 ], [ 1, %if.end310 ], [ 1, %if.end318 ]
  %78 = add nsw i64 %41, 1
  %arrayidx314.1 = getelementptr inbounds i32, i32* %nodes_capacities, i64 %78
  %79 = load i32, i32* %arrayidx314.1, align 4
  %cmp315.1 = icmp eq i32 %79, -1
  br i1 %cmp315.1, label %if.then316.1, label %if.end318.1

if.end318.1:                                      ; preds = %if.end310.1
  %arrayidx322.1 = getelementptr inbounds i32, i32* %nodes_curr_capacities, i64 %78
  %80 = load i32, i32* %arrayidx322.1, align 4
  %cmp327.1 = icmp eq i32 %80, %79
  br i1 %cmp327.1, label %if.then328.1, label %if.end330.1

if.end330.1:                                      ; preds = %if.end318.1
  %idxprom331.1 = sext i32 %add301 to i64
  %arrayidx332.1 = getelementptr inbounds i32, i32* %heights, i64 %idxprom331.1
  %81 = load i32, i32* %arrayidx332.1, align 4
  %cmp333.1 = icmp slt i32 %81, %min_height.2
  br i1 %cmp333.1, label %if.then334.1, label %if.end310.2

if.then334.1:                                     ; preds = %if.end330.1
  %add337.1 = add nsw i32 %81, 1
  store i32 %add337.1, i32* %arrayidx339, align 4
  br label %if.end310.2

if.then328.1:                                     ; preds = %if.end318.1
  %inc329.1 = add nuw nsw i32 %continue_count272.1, 1
  br label %if.end310.2

if.then316.1:                                     ; preds = %if.end310.1
  %inc317.1 = add nuw nsw i32 %continue_count272.1, 1
  br label %if.end310.2

if.end310.2:                                      ; preds = %if.then316.1, %if.then328.1, %if.then334.1, %if.end330.1
  %min_height.2.1 = phi i32 [ %min_height.2, %if.then316.1 ], [ %min_height.2, %if.then328.1 ], [ %81, %if.then334.1 ], [ %min_height.2, %if.end330.1 ]
  %continue_count272.1.1 = phi i32 [ %inc317.1, %if.then316.1 ], [ %inc329.1, %if.then328.1 ], [ %continue_count272.1, %if.then334.1 ], [ %continue_count272.1, %if.end330.1 ]
  %82 = add nsw i64 %41, 2
  %arrayidx314.2 = getelementptr inbounds i32, i32* %nodes_capacities, i64 %82
  %83 = load i32, i32* %arrayidx314.2, align 4
  %cmp315.2 = icmp eq i32 %83, -1
  br i1 %cmp315.2, label %if.then316.2, label %if.end318.2

if.end318.2:                                      ; preds = %if.end310.2
  %arrayidx322.2 = getelementptr inbounds i32, i32* %nodes_curr_capacities, i64 %82
  %84 = load i32, i32* %arrayidx322.2, align 4
  %cmp327.2 = icmp eq i32 %84, %83
  br i1 %cmp327.2, label %if.then328.2, label %if.end330.2

if.end330.2:                                      ; preds = %if.end318.2
  %idxprom331.2 = sext i32 %add305 to i64
  %arrayidx332.2 = getelementptr inbounds i32, i32* %heights, i64 %idxprom331.2
  %85 = load i32, i32* %arrayidx332.2, align 4
  %cmp333.2 = icmp slt i32 %85, %min_height.2.1
  br i1 %cmp333.2, label %if.then334.2, label %if.end310.3

if.then334.2:                                     ; preds = %if.end330.2
  %add337.2 = add nsw i32 %85, 1
  store i32 %add337.2, i32* %arrayidx339, align 4
  br label %if.end310.3

if.then328.2:                                     ; preds = %if.end318.2
  %inc329.2 = add nsw i32 %continue_count272.1.1, 1
  br label %if.end310.3

if.then316.2:                                     ; preds = %if.end310.2
  %inc317.2 = add nsw i32 %continue_count272.1.1, 1
  br label %if.end310.3

if.end310.3:                                      ; preds = %if.then316.2, %if.then328.2, %if.then334.2, %if.end330.2
  %min_height.2.2 = phi i32 [ %min_height.2.1, %if.then316.2 ], [ %min_height.2.1, %if.then328.2 ], [ %85, %if.then334.2 ], [ %min_height.2.1, %if.end330.2 ]
  %continue_count272.1.2 = phi i32 [ %inc317.2, %if.then316.2 ], [ %inc329.2, %if.then328.2 ], [ %continue_count272.1.1, %if.then334.2 ], [ %continue_count272.1.1, %if.end330.2 ]
  %86 = add nsw i64 %41, 3
  %arrayidx314.3 = getelementptr inbounds i32, i32* %nodes_capacities, i64 %86
  %87 = load i32, i32* %arrayidx314.3, align 4
  %cmp315.3 = icmp eq i32 %87, -1
  br i1 %cmp315.3, label %for.inc341.3, label %if.end318.3

if.end318.3:                                      ; preds = %if.end310.3
  %arrayidx322.3 = getelementptr inbounds i32, i32* %nodes_curr_capacities, i64 %86
  %88 = load i32, i32* %arrayidx322.3, align 4
  %cmp327.3 = icmp eq i32 %88, %87
  br i1 %cmp327.3, label %for.inc341.3, label %if.end330.3

if.end330.3:                                      ; preds = %if.end318.3
  %idxprom331.3 = sext i32 %sub307 to i64
  %arrayidx332.3 = getelementptr inbounds i32, i32* %heights, i64 %idxprom331.3
  %89 = load i32, i32* %arrayidx332.3, align 4
  %cmp333.3 = icmp slt i32 %89, %min_height.2.2
  br i1 %cmp333.3, label %if.then334.3, label %for.body409.preheader

if.then334.3:                                     ; preds = %if.end330.3
  %add337.3 = add nsw i32 %89, 1
  store i32 %add337.3, i32* %arrayidx339, align 4
  br label %for.body409.preheader

for.inc341.3:                                     ; preds = %if.end318.3, %if.end310.3
  %cmp344 = icmp eq i32 %continue_count272.1.2, 3
  br i1 %cmp344, label %if.end366, label %for.body409.preheader

if.end366.1:                                      ; preds = %if.end374, %if.end366, %if.end382, %if.then386
  %min_height.5 = phi i32 [ %48, %if.then386 ], [ %min_height.2.2, %if.end382 ], [ %min_height.2.2, %if.end366 ], [ %min_height.2.2, %if.end374 ]
  %continue_count272.3 = phi i32 [ 0, %if.then386 ], [ 0, %if.end382 ], [ 1, %if.end366 ], [ 1, %if.end374 ]
  %90 = add nsw i64 %45, 1
  %arrayidx370.1 = getelementptr inbounds i32, i32* %nodes_capacities, i64 %90
  %91 = load i32, i32* %arrayidx370.1, align 4
  %cmp371.1 = icmp eq i32 %91, -1
  br i1 %cmp371.1, label %if.then372.1, label %if.end374.1

if.end374.1:                                      ; preds = %if.end366.1
  %arrayidx378.1 = getelementptr inbounds i32, i32* %res_curr_capacities, i64 %90
  %92 = load i32, i32* %arrayidx378.1, align 4
  %cmp379.1 = icmp slt i32 %92, 1
  br i1 %cmp379.1, label %if.then380.1, label %if.end382.1

if.end382.1:                                      ; preds = %if.end374.1
  %idxprom383.1 = sext i32 %add357 to i64
  %arrayidx384.1 = getelementptr inbounds i32, i32* %heights, i64 %idxprom383.1
  %93 = load i32, i32* %arrayidx384.1, align 4
  %cmp385.1 = icmp slt i32 %93, %min_height.5
  br i1 %cmp385.1, label %if.then386.1, label %if.end366.2

if.then386.1:                                     ; preds = %if.end382.1
  %add389.1 = add nsw i32 %93, 1
  store i32 %add389.1, i32* %arrayidx391, align 4
  br label %if.end366.2

if.then380.1:                                     ; preds = %if.end374.1
  %inc381.1 = add nuw nsw i32 %continue_count272.3, 1
  br label %if.end366.2

if.then372.1:                                     ; preds = %if.end366.1
  %inc373.1 = add nuw nsw i32 %continue_count272.3, 1
  br label %if.end366.2

if.end366.2:                                      ; preds = %if.then372.1, %if.then380.1, %if.then386.1, %if.end382.1
  %min_height.5.1 = phi i32 [ %min_height.5, %if.then372.1 ], [ %min_height.5, %if.then380.1 ], [ %93, %if.then386.1 ], [ %min_height.5, %if.end382.1 ]
  %continue_count272.3.1 = phi i32 [ %inc373.1, %if.then372.1 ], [ %inc381.1, %if.then380.1 ], [ %continue_count272.3, %if.then386.1 ], [ %continue_count272.3, %if.end382.1 ]
  %94 = add nsw i64 %45, 2
  %arrayidx370.2 = getelementptr inbounds i32, i32* %nodes_capacities, i64 %94
  %95 = load i32, i32* %arrayidx370.2, align 4
  %cmp371.2 = icmp eq i32 %95, -1
  br i1 %cmp371.2, label %if.then372.2, label %if.end374.2

if.end374.2:                                      ; preds = %if.end366.2
  %arrayidx378.2 = getelementptr inbounds i32, i32* %res_curr_capacities, i64 %94
  %96 = load i32, i32* %arrayidx378.2, align 4
  %cmp379.2 = icmp slt i32 %96, 1
  br i1 %cmp379.2, label %if.then380.2, label %if.end382.2

if.end382.2:                                      ; preds = %if.end374.2
  %idxprom383.2 = sext i32 %add361 to i64
  %arrayidx384.2 = getelementptr inbounds i32, i32* %heights, i64 %idxprom383.2
  %97 = load i32, i32* %arrayidx384.2, align 4
  %cmp385.2 = icmp slt i32 %97, %min_height.5.1
  br i1 %cmp385.2, label %if.then386.2, label %if.end366.3

if.then386.2:                                     ; preds = %if.end382.2
  %add389.2 = add nsw i32 %97, 1
  store i32 %add389.2, i32* %arrayidx391, align 4
  br label %if.end366.3

if.then380.2:                                     ; preds = %if.end374.2
  %inc381.2 = add nsw i32 %continue_count272.3.1, 1
  br label %if.end366.3

if.then372.2:                                     ; preds = %if.end366.2
  %inc373.2 = add nsw i32 %continue_count272.3.1, 1
  br label %if.end366.3

if.end366.3:                                      ; preds = %if.then372.2, %if.then380.2, %if.then386.2, %if.end382.2
  %min_height.5.2 = phi i32 [ %min_height.5.1, %if.then372.2 ], [ %min_height.5.1, %if.then380.2 ], [ %97, %if.then386.2 ], [ %min_height.5.1, %if.end382.2 ]
  %continue_count272.3.2 = phi i32 [ %inc373.2, %if.then372.2 ], [ %inc381.2, %if.then380.2 ], [ %continue_count272.3.1, %if.then386.2 ], [ %continue_count272.3.1, %if.end382.2 ]
  %98 = add nsw i64 %45, 3
  %arrayidx370.3 = getelementptr inbounds i32, i32* %nodes_capacities, i64 %98
  %99 = load i32, i32* %arrayidx370.3, align 4
  %cmp371.3 = icmp eq i32 %99, -1
  br i1 %cmp371.3, label %for.inc393.3, label %if.end374.3

if.end374.3:                                      ; preds = %if.end366.3
  %arrayidx378.3 = getelementptr inbounds i32, i32* %res_curr_capacities, i64 %98
  %100 = load i32, i32* %arrayidx378.3, align 4
  %cmp379.3 = icmp slt i32 %100, 1
  br i1 %cmp379.3, label %for.inc393.3, label %if.end382.3

if.end382.3:                                      ; preds = %if.end374.3
  %idxprom383.3 = sext i32 %sub363 to i64
  %arrayidx384.3 = getelementptr inbounds i32, i32* %heights, i64 %idxprom383.3
  %101 = load i32, i32* %arrayidx384.3, align 4
  %cmp385.3 = icmp slt i32 %101, %min_height.5.2
  br i1 %cmp385.3, label %if.then386.3, label %for.body409.preheader

if.then386.3:                                     ; preds = %if.end382.3
  %add389.3 = add nsw i32 %101, 1
  store i32 %add389.3, i32* %arrayidx391, align 4
  br label %for.body409.preheader

for.inc393.3:                                     ; preds = %if.end374.3, %if.end366.3
  %cmp397 = icmp eq i32 %continue_count272.3.2, 3
  br i1 %cmp397, label %if.then398, label %for.body409.preheader

if.end.1:                                         ; preds = %if.end
  %arrayidx17.2 = getelementptr inbounds i32, i32* %excess_flows, i64 2
  %102 = load i32, i32* %arrayidx17.2, align 4
  %cmp18.2 = icmp sgt i32 %102, 0
  br i1 %cmp18.2, label %while.body.preheader, label %if.end.2

if.end.2:                                         ; preds = %if.end.1
  %arrayidx17.3 = getelementptr inbounds i32, i32* %excess_flows, i64 3
  %103 = load i32, i32* %arrayidx17.3, align 4
  %cmp18.3 = icmp sgt i32 %103, 0
  br i1 %cmp18.3, label %while.body.preheader, label %if.end.3

if.end.3:                                         ; preds = %if.end.2
  %arrayidx17.4 = getelementptr inbounds i32, i32* %excess_flows, i64 4
  %104 = load i32, i32* %arrayidx17.4, align 4
  %cmp18.4 = icmp sgt i32 %104, 0
  br i1 %cmp18.4, label %while.body.preheader, label %if.end.4

if.end.4:                                         ; preds = %if.end.3
  %arrayidx17.5 = getelementptr inbounds i32, i32* %excess_flows, i64 5
  %105 = load i32, i32* %arrayidx17.5, align 4
  %cmp18.5 = icmp sgt i32 %105, 0
  br i1 %cmp18.5, label %while.body.preheader, label %if.end.5

if.end.5:                                         ; preds = %if.end.4
  %arrayidx17.6 = getelementptr inbounds i32, i32* %excess_flows, i64 6
  %106 = load i32, i32* %arrayidx17.6, align 4
  %cmp18.6 = icmp sgt i32 %106, 0
  br i1 %cmp18.6, label %while.body.preheader, label %if.end.6

if.end.6:                                         ; preds = %if.end.5
  %arrayidx17.7 = getelementptr inbounds i32, i32* %excess_flows, i64 7
  %107 = load i32, i32* %arrayidx17.7, align 4
  %cmp18.7 = icmp sgt i32 %107, 0
  br i1 %cmp18.7, label %while.body.preheader, label %if.end.7

if.end.7:                                         ; preds = %if.end.6
  %arrayidx17.8 = getelementptr inbounds i32, i32* %excess_flows, i64 8
  %108 = load i32, i32* %arrayidx17.8, align 4
  %cmp18.8 = icmp sgt i32 %108, 0
  br i1 %cmp18.8, label %while.body.preheader, label %if.end.8

if.end.8:                                         ; preds = %if.end.7
  %arrayidx17.9 = getelementptr inbounds i32, i32* %excess_flows, i64 9
  %109 = load i32, i32* %arrayidx17.9, align 4
  %cmp18.9 = icmp sgt i32 %109, 0
  br i1 %cmp18.9, label %while.body.preheader, label %if.end.9

if.end.9:                                         ; preds = %if.end.8
  %arrayidx17.10 = getelementptr inbounds i32, i32* %excess_flows, i64 10
  %110 = load i32, i32* %arrayidx17.10, align 4
  %cmp18.10 = icmp sgt i32 %110, 0
  br i1 %cmp18.10, label %while.body.preheader, label %if.end.10

if.end.10:                                        ; preds = %if.end.9
  %arrayidx17.11 = getelementptr inbounds i32, i32* %excess_flows, i64 11
  %111 = load i32, i32* %arrayidx17.11, align 4
  %cmp18.11 = icmp sgt i32 %111, 0
  br i1 %cmp18.11, label %while.body.preheader, label %if.end.11

if.end.11:                                        ; preds = %if.end.10
  %arrayidx17.12 = getelementptr inbounds i32, i32* %excess_flows, i64 12
  %112 = load i32, i32* %arrayidx17.12, align 4
  %cmp18.12 = icmp sgt i32 %112, 0
  br i1 %cmp18.12, label %while.body.preheader, label %if.end.12

if.end.12:                                        ; preds = %if.end.11
  %arrayidx17.13 = getelementptr inbounds i32, i32* %excess_flows, i64 13
  %113 = load i32, i32* %arrayidx17.13, align 4
  %cmp18.13 = icmp sgt i32 %113, 0
  br i1 %cmp18.13, label %while.body.preheader, label %if.end.13

if.end.13:                                        ; preds = %if.end.12
  %arrayidx17.14 = getelementptr inbounds i32, i32* %excess_flows, i64 14
  %114 = load i32, i32* %arrayidx17.14, align 4
  %cmp18.14 = icmp sgt i32 %114, 0
  br i1 %cmp18.14, label %while.body.preheader, label %if.end.14

if.end.14:                                        ; preds = %if.end.13
  %arrayidx17.15 = getelementptr inbounds i32, i32* %excess_flows, i64 15
  %115 = load i32, i32* %arrayidx17.15, align 4
  %cmp18.15 = icmp sgt i32 %115, 0
  br i1 %cmp18.15, label %while.body.preheader, label %if.end.15

if.end.15:                                        ; preds = %if.end.14
  %arrayidx17.16 = getelementptr inbounds i32, i32* %excess_flows, i64 16
  %116 = load i32, i32* %arrayidx17.16, align 4
  %cmp18.16 = icmp sgt i32 %116, 0
  br i1 %cmp18.16, label %while.body.preheader, label %if.end.16

if.end.16:                                        ; preds = %if.end.15
  %arrayidx17.17 = getelementptr inbounds i32, i32* %excess_flows, i64 17
  %117 = load i32, i32* %arrayidx17.17, align 4
  %cmp18.17 = icmp sgt i32 %117, 0
  br i1 %cmp18.17, label %while.body.preheader, label %if.end.17

if.end.17:                                        ; preds = %if.end.16
  %arrayidx17.18 = getelementptr inbounds i32, i32* %excess_flows, i64 18
  %118 = load i32, i32* %arrayidx17.18, align 4
  %cmp18.18 = icmp sgt i32 %118, 0
  br i1 %cmp18.18, label %while.body.preheader, label %if.end.18

if.end.18:                                        ; preds = %if.end.17
  %arrayidx17.19 = getelementptr inbounds i32, i32* %excess_flows, i64 19
  %119 = load i32, i32* %arrayidx17.19, align 4
  %cmp18.19 = icmp sgt i32 %119, 0
  br i1 %cmp18.19, label %while.body.preheader, label %if.end.19

if.end.19:                                        ; preds = %if.end.18
  %arrayidx17.20 = getelementptr inbounds i32, i32* %excess_flows, i64 20
  %120 = load i32, i32* %arrayidx17.20, align 4
  %cmp18.20 = icmp sgt i32 %120, 0
  br i1 %cmp18.20, label %while.body.preheader, label %if.end.20

if.end.20:                                        ; preds = %if.end.19
  %arrayidx17.21 = getelementptr inbounds i32, i32* %excess_flows, i64 21
  %121 = load i32, i32* %arrayidx17.21, align 4
  %cmp18.21 = icmp sgt i32 %121, 0
  br i1 %cmp18.21, label %while.body.preheader, label %if.end.21

if.end.21:                                        ; preds = %if.end.20
  %arrayidx17.22 = getelementptr inbounds i32, i32* %excess_flows, i64 22
  %122 = load i32, i32* %arrayidx17.22, align 4
  %cmp18.22 = icmp sgt i32 %122, 0
  br i1 %cmp18.22, label %while.body.preheader, label %if.end.22

if.end.22:                                        ; preds = %if.end.21
  %arrayidx17.23 = getelementptr inbounds i32, i32* %excess_flows, i64 23
  %123 = load i32, i32* %arrayidx17.23, align 4
  %cmp18.23 = icmp sgt i32 %123, 0
  br i1 %cmp18.23, label %while.body.preheader, label %if.end.23

if.end.23:                                        ; preds = %if.end.22
  %arrayidx17.24 = getelementptr inbounds i32, i32* %excess_flows, i64 24
  %124 = load i32, i32* %arrayidx17.24, align 4
  %cmp18.24 = icmp sgt i32 %124, 0
  br i1 %cmp18.24, label %while.body.preheader, label %while.end
}

attributes #0 = { norecurse nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.1 "}
