
hm = 0;

for i = 1:10;
    if i < 5
        hm = hm + 1
    elseif i == 5
        hm = hm -5
    else
        hm = hm + 3
    end
    fprintf(i + " " + hm)
end

disp(hm);
    
    