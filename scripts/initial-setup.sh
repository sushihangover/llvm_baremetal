#
#
# Avoid non-linear history in the llvm repos:
# http://llvm.org/docs/GettingStarted.html
#
pushd sources/llvm
git config branch.master.rebase true
git config rebase.stat true
popd
#
#
#

