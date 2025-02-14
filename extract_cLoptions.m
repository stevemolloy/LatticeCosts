function extract_cLoptions()
    % Define the base directory
    baseDir = fullfile('data', 'CandidateLattices');
    
    % Get a list of all folders inside the base directory
    folders = dir(baseDir);
    
    % Loop through each folder
    for i = 1:length(folders)
        if folders(i).isdir && ~startsWith(folders(i).name, '.') % Ignore '.' and '..' and hidden folders
            folderName = folders(i).name;
            folderPath = fullfile(baseDir, folderName);
            
            % Define the expected mat-file name
            matFileName = fullfile(folderPath, [folderName, '.mat']);
            
            % Check if the mat file exists
            if exist(matFileName, 'file')
                fprintf('Processing: %s\n', matFileName);
                
                % Load the MAT file
                data = load(matFileName);
                
                % Extract the struct (assuming there's only one variable in the file)
                structFields = fieldnames(data);
                if numel(structFields) == 1
                    structData = data.(structFields{1});
                    
                    % Check if "cLoptions" exists in the struct
                    if isfield(structData, 'cLoptions')
                        cLoptions = structData.cLoptions;
                        
                        % Define the output file path
                        outputFile = fullfile(folderPath, 'cLoptions.mat');
                        
                        % Save the cLoptions variable
                        save(outputFile, 'cLoptions');
                        
                        fprintf('Saved cLoptions in %s\n', outputFile);
                    else
                        fprintf('Warning: No "cLoptions" field in %s\n', matFileName);
                    end
                else
                    fprintf('Warning: Unexpected structure in %s\n', matFileName);
                end
                
                % Clear variables to free memory
                clear data structData cLoptions;
            end
        end
    end
end

