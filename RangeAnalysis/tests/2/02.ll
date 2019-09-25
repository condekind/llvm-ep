; ModuleID = '<stdin>'
source_filename = "tests/2/02.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline norecurse nounwind uwtable
define dso_local i32 @main() #0 {
entry:
  br label %while.cond

while.cond:                                       ; preds = %while.end, %entry
  %k.0 = phi i32 [ 0, %entry ], [ %add4, %while.end ]
  %cmp = icmp slt i32 %k.0, 100
  br i1 %cmp, label %while.body, label %while.end5

while.body:                                       ; preds = %while.cond
  %vSSA_sigma = phi i32 [ %k.0, %while.cond ]
  br label %while.cond1

while.cond1:                                      ; preds = %while.body3, %while.body
  %i.0 = phi i32 [ 0, %while.body ], [ %add, %while.body3 ]
  %j.0 = phi i32 [ %vSSA_sigma, %while.body ], [ %sub, %while.body3 ]
  %cmp2 = icmp slt i32 %i.0, %j.0
  br i1 %cmp2, label %while.body3, label %while.end

while.body3:                                      ; preds = %while.cond1
  %vSSA_sigma3 = phi i32 [ %j.0, %while.cond1 ]
  %vSSA_sigma2 = phi i32 [ %i.0, %while.cond1 ]
  %add = add nsw i32 %vSSA_sigma2, 1
  %sub = sub nsw i32 %vSSA_sigma3, 1
  br label %while.cond1

while.end:                                        ; preds = %while.cond1
  %add4 = add nsw i32 %vSSA_sigma, 1
  br label %while.cond

while.end5:                                       ; preds = %while.cond
  %vSSA_sigma1 = phi i32 [ %k.0, %while.cond ]
  ret i32 %vSSA_sigma1
}

attributes #0 = { noinline norecurse nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 8.0.0 (tags/RELEASE_800/final 361874) (llvm/tags/RELEASE_800/final 361870)"}
