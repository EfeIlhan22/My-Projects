package website.api.service;

import website.api.dto.YorumDto;
import website.api.dto.YorumResponse;

public interface YorumService {
    YorumDto createYorum(YorumDto yorumDto);

    YorumResponse getAllYorums(int pageNumber , int pageSize);

    YorumDto getYorumById(int id);

    YorumDto updateYorumById(YorumDto yorumDto , int id);

    void deleteYorumById(int id);
    
}
