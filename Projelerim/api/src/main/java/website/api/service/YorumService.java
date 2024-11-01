package website.api.service;

import java.util.List;

import website.api.dto.YorumDto;

public interface YorumService {
    YorumDto createYorum(int hoca_id, YorumDto yorumDto);

    YorumDto updateYorumById(YorumDto yorumDto , int yorum_id, int hoca_id);

    void deleteYorumById(int yorum_id,int hoca_id);

    List<YorumDto> getYorumByHocaId(int id);    
}
