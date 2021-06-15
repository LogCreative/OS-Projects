Get-ChildItem . '*.tex' -Force -Recurse | ForEach-Object -Parallel {
    $file = [io.Path]::Combine($_.DirectoryName, $_.FullName)

    (Get-Content $file)|
        ForEach-Object { $_ -replace '***','Log Creative'} |  # Change Name
        ForEach-Object { $_ -replace '***********',''} | # Change Number
        Out-File $file -Force 
    
    cd $_.DirectoryName 
    latexmk -pdf $file -interaction=nonstopmode --shell-escape
}